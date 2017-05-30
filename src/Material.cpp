#include <iostream>
#include <cstdlib>

#include "Material.h"

using namespace eyesore;

using std::string;

const string eyesore::Material::MATERIAL_PATH = "../materials/";

eyesore::Material::Material(string name)
{
	string path = MATERIAL_PATH + name + "/";

	albedo = new Texture(path + "albedo.png");
	normal = new Texture(path + "normal.png");
	metallic = new Texture(path + "metalness.png");
	roughness = new Texture(path + "roughness.png");

	GLint program;

	glGetIntegerv(GL_CURRENT_PROGRAM, &program);

	glUniform1i(glGetUniformLocation(program, "albedo_map"), 0);
	glUniform1i(glGetUniformLocation(program, "normal_map"), 1);
	glUniform1i(glGetUniformLocation(program, "metallic_map"), 2);
	glUniform1i(glGetUniformLocation(program, "roughness_map"), 3);
}

void eyesore::Material::use()
{
	GLint program;

	glGetIntegerv(GL_CURRENT_PROGRAM, &program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, albedo->get());

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, normal->get());

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, metallic->get());

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, roughness->get());
}

