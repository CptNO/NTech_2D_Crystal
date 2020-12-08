#include "Shader.h"


namespace NTCrystal {
	namespace Graphics{
	
		Shader::Shader(const char *vertPath, const char *fragPath)
		{
			m_vertPath = vertPath;
			m_fragPath = fragPath;
			m_shaderID = load();
		}

		Shader::~Shader()
		{
			glDeleteProgram(m_shaderID);
		}

		GLuint Shader::load(){
			GLuint program = glCreateProgram();
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertSourceString = FileUtils::read_file(m_vertPath);
			std::string fragSourceString = FileUtils::read_file(m_fragPath);
			const char *vertSource = vertSourceString.c_str();
			const char *fragSource = fragSourceString.c_str();
			
			glShaderSource(fragment, 1, &fragSource, NULL);
			compileShader(fragSource, fragment);
			glShaderSource(vertex, 1, &vertSource, NULL);
			compileShader(vertSource, vertex);

			glAttachShader(program, fragment);
			glAttachShader(program, vertex);

			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(vertex);
			glDeleteShader(fragment);

			return program;
		}

		GLuint Shader::compileShader(const char *shaderSourceCode, GLuint shaderID)
		{
			glShaderSource(shaderID, 1, &shaderSourceCode, NULL);
			glCompileShader(shaderID);

			GLint result;
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE){
				GLint leinght;
				glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &leinght);
				std::vector<char> error(leinght);
				glGetShaderInfoLog(shaderID, leinght, &leinght, &error[0]);
				std::cout << "Error ShaderID: " << shaderID << "\n" << &error[0] << std::endl;
				glDeleteShader(shaderID);
				return 0;
			}
			return result;
		}

		GLint Shader::getUniformLocation(const GLchar *name)
		{
			return glGetUniformLocation(m_shaderID, name);
		}

		void Shader::enable() const
		{
			glUseProgram(m_shaderID);
		}

		void Shader::disable() const
		{
			glUseProgram(0);
		}

		void Shader::setUniformMat4(const GLchar *name, const math::mat4 &matrix)
		{
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE,  matrix.elements);
		}

		void Shader::setUniform1f(const GLchar *name, float value)
		{
			glUniform1f(getUniformLocation(name), value); 
		}

		void Shader::setUniform1i(const GLchar *name, int value)
		{
			glUniform1i(getUniformLocation(name), value);
		}

		void Shader::setUniform2f(const GLchar *name, const math::vec2 &vector)
		{
			glUniform2f(getUniformLocation(name), vector.x , vector.y);
		}

		void Shader::setUniform3f(const GLchar *name, const math::vec3 &vector)
		{
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		}

		void Shader::setUniform4f(const GLchar *name, const math::vec4 &vector)
		{
			glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}

	}
}