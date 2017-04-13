#include <fstream>
#include <sstream>

#include "Shader.h"

using std::string;
using std::ifstream;
using std::stringstream;

eyesore::Shader::Shader()
{
	id = 0;
}

eyesore::Shader::Shader(const string path, GLenum type)
{
	id = glCreateShader(type);

	ifstream file(path);
	stringstream stream;

	stream << file.rdbuf();

	string source = stream.str();
	const char *sourceCopy = source.c_str();

	glShaderSource(id, 1, &sourceCopy, nullptr);
	glCompileShader(id);
}

eyesore::Shader::~Shader()
{
	glDeleteShader(id);
}

GLuint eyesore::Shader::get()
{
	return id;
}

