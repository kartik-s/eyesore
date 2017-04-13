#include "ShaderProgram.h"

eyesore::ShaderProgram::ShaderProgram()
{
	id = glCreateProgram();
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
	glLinkProgram(id);
	glUseProgram(id);
}

