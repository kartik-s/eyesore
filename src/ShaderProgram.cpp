#include "ShaderProgram.h"

eyesore::ShaderProgram::ShaderProgram()
{
	id = glCreateProgram();
	id = 0;
}

eyesore::ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(id);
}

void eyesore::ShaderProgram::attach(GLuint shader)
{
	glAttachShader(id, shader);
}

void eyesore::ShaderProgram::use() const
{
	glUseProgram(id);
}

