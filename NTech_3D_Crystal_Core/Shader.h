#pragma once
#include "fileUtils.h"
#include <glew.h>
#include <vector>
#include "maths.h"

namespace NTCrystal {
	namespace Graphics{
		class Shader
		{
		public:
			Shader(const char* vertPath, const char* fragPath);
			~Shader();

			void enable() const;
			void disable() const;

			GLuint getShaderID()const { return m_shaderID; }

			void setUniformMat4(const GLchar *name, const math::mat4 &matrix);
			void setUniform1f(const GLchar *name, float value);
			void setUniform1i(const GLchar *name, int value); 
			void setUniform2f(const GLchar *name, const math::vec2 &vector);
			void setUniform3f(const GLchar *name, const math::vec3 &vector);
			void setUniform4f(const GLchar *name, const math::vec4 &vector);
		private:
			const char *m_vertPath;
			const char *m_fragPath;
			GLuint m_shaderID;
			GLuint load();
			GLuint compileShader(const char *shaderSourceCode, GLuint shaderID);
			GLint getUniformLocation(const GLchar *name);
		};

	}

}