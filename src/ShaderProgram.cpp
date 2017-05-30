#include <iostream>

#include "ShaderProgram.h"
#include "Shader.h"

using namespace eyesore;

eyesore::ShaderProgram::ShaderProgram()
{
	id = glCreateProgram();
}

eyesore::ShaderProgram::~ShaderProgram()
{

}

GLuint eyesore::ShaderProgram::get() const
{
	return id;
}

void eyesore::ShaderProgram::attach(Shader shader)
{
	glAttachShader(id, shader.get());
}

void eyesore::ShaderProgram::link() const
{
	glLinkProgram(id);
}

void eyesore::ShaderProgram::use() const
{
	glUseProgram(id);
}

