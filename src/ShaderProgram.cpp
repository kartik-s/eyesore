#include "ShaderProgram.h"
#include "Shader.h"

using namespace eyesore;

eyesore::ShaderProgram::ShaderProgram()
{
	id = glCreateProgram();
}

eyesore::ShaderProgram::~ShaderProgram()
{
	glDeleteProgram(id);
}

void eyesore::ShaderProgram::attach(Shader shader)
{
	glAttachShader(id, shader.get());
}

void eyesore::ShaderProgram::use() const
{
	glLinkProgram(id);
	glUseProgram(id);
}

