#pragma once


#include <string>
#include <glew.h>

//This class handles the compilation, linking, and usage of a GLSL shader program.
//Reference: http://www.opengl.org/wiki/Shader_Compilation
class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void compileShader(const std::string &vertexShaderFilePath, const std::string &fragmentShaderFilePath);

	void linkShaders();

	void addAttribute(const std::string &attributeName);

	GLint getUniformLocation(const std::string &uniformName);
	void use();
	void unuse();
private:
	int _numAttributes;

	void compileShader(const std::string &filePath, GLuint id);

	GLuint _programID;

	//this will probably be array later
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;

};

