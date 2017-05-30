#include "Environment.h"
#include "Shader.h"
#include "Vertex.h"

#include <iostream>
#include <vector>
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stb_image.h>

using namespace eyesore;

using std::string;
using std::vector;

using glm::vec2;
using glm::vec3;
using glm::mat4;

const string eyesore::Environment::ENV_PATH = "../environments/";

static void renderQuad()
{
	float data[] = {
		-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 0.0f
	};
	vector<Vertex> vertices;
	vector<GLuint> indices;

	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(1);
	indices.push_back(3);
	indices.push_back(2);

	for (int i = 0; i < 4; i++) {
		vec3 pos(data[i*5], data[i*5 + 1], data[i*5 + 2]);
		vec2 uv(data[i*5 + 3], data[i*5 + 4]);

		vertices.push_back(Vertex(pos, uv));
	}

	Mesh quad(vertices, indices);

	quad.render();
}

eyesore::Environment::Environment(string name, Camera *camera): cube("cube.obj"),
	camera(camera)
{
	int width, height, n;
	string path = ENV_PATH + name;

	stbi_set_flip_vertically_on_load(true);

	float *data = stbi_loadf(path.c_str(), &width, &height, &n, 0);

	glGenTextures(1, &hdri);
	glBindTexture(GL_TEXTURE_2D, hdri);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_image_free(data);

	makeMaps();

	Shader vert("../shaders/skybox.vert", GL_VERTEX_SHADER);
	Shader frag("../shaders/skybox.frag", GL_FRAGMENT_SHADER);

	skybox.attach(vert);
	skybox.attach(frag);
	skybox.link();
}

void eyesore::Environment::use()
{
	GLint program;

	glGetIntegerv(GL_CURRENT_PROGRAM, &program);

	glUniform1i(glGetUniformLocation(program, "irradiance_map"), 5);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_CUBE_MAP, irradiance);

	glUniform1i(glGetUniformLocation(program, "prefilter_map"), 6);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_CUBE_MAP, prefilter);

	glUniform1i(glGetUniformLocation(program, "irradiance_map"), 7);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D, brdfLUT);

}

void eyesore::Environment::render()
{
	skybox.use();

	glUniform1i(glGetUniformLocation(skybox.get(), "environment_map"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);

	glUniformMatrix4fv(glGetUniformLocation(skybox.get(), "view"), 1, GL_FALSE, glm::value_ptr(camera->getView()));
	glUniformMatrix4fv(glGetUniformLocation(skybox.get(), "projection"), 1, GL_FALSE, glm::value_ptr(camera->getProjection()));

	cube.render();
}

void eyesore::Environment::makeMaps()
{
	GLuint fbo, rbo;

	glGenFramebuffers(1, &fbo);
	glGenRenderbuffers(1, &rbo);

	mat4 projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
	mat4 views[] = {
		glm::lookAt(vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f)),
		glm::lookAt(vec3(0.0f, 0.0f, 0.0f), vec3(-1.0f, 0.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f)),
		glm::lookAt(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f)),
		glm::lookAt(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, -1.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f)),
		glm::lookAt(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, -1.0f, 0.0f)),
		glm::lookAt(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, -1.0f, 0.0f))
	};

	makeCubemap(fbo, rbo, projection, views);
	makeIrradianceMap(fbo, rbo, projection, views);
	makePrefilterMap(fbo, rbo, projection, views);
	makeBRDFLUT(fbo, rbo);
}

void eyesore::Environment::makeCubemap(GLuint fbo, GLuint rbo, mat4 projection, mat4 *views)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, CUBEMAP_RES, CUBEMAP_RES);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);

	glGenTextures(1, &cubemap);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);

	for (int i = 0; i < 6; i++)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, CUBEMAP_RES, CUBEMAP_RES, 0, GL_RGB, GL_FLOAT, nullptr);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	Shader vert("../shaders/cubemap.vert", GL_VERTEX_SHADER);
	Shader frag("../shaders/equirect_to_cube.frag", GL_FRAGMENT_SHADER);
	ShaderProgram shader;

	shader.attach(vert);
	shader.attach(frag);
	shader.link();
	shader.use();

	glUniform1i(glGetUniformLocation(shader.get(), "equirectangular_map"), 0);
	glUniformMatrix4fv(glGetUniformLocation(shader.get(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, hdri);

	glViewport(0, 0, CUBEMAP_RES, CUBEMAP_RES);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	for (int i = 0; i < 6; i++) {
		glUniformMatrix4fv(glGetUniformLocation(shader.get(), "view"), 1, GL_FALSE, glm::value_ptr(views[i]));
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, cubemap, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cube.render();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void eyesore::Environment::makeIrradianceMap(GLuint fbo, GLuint rbo, mat4 projection, mat4 *views)
{
	glGenTextures(1, &irradiance);
	glBindTexture(GL_TEXTURE_CUBE_MAP, irradiance);

	for (int i = 0; i < 6; i++)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 32, 32, 0, GL_RGB, GL_FLOAT, nullptr);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 32, 32);

	Shader vert("../shaders/cubemap.vert", GL_VERTEX_SHADER);
	Shader frag("../shaders/diffuse_convolve.frag", GL_FRAGMENT_SHADER);
	ShaderProgram shader;

	shader.attach(vert);
	shader.attach(frag);
	shader.link();
	shader.use();

	glUniform1i(glGetUniformLocation(shader.get(), "environment_map"), 0);
	glUniformMatrix4fv(glGetUniformLocation(shader.get(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);

	glViewport(0, 0, 32, 32);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	for (int i = 0; i < 6; i++) {
		glUniformMatrix4fv(glGetUniformLocation(shader.get(), "view"), 1, GL_FALSE, glm::value_ptr(views[i]));
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, irradiance, 0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		cube.render();
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void eyesore::Environment::makePrefilterMap(GLuint fbo, GLuint rbo, glm::mat4 projection, glm::mat4 *views)
{
	glGenTextures(1, &prefilter);
	glBindTexture(GL_TEXTURE_CUBE_MAP, prefilter);

	for (int i = 0; i < 6; i++)
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, 128, 128, 0, GL_RGB, GL_FLOAT, nullptr);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

	Shader vert("../shaders/cubemap.vert", GL_VERTEX_SHADER);
	Shader frag("../shaders/prefilter.frag", GL_FRAGMENT_SHADER);
	ShaderProgram shader;

	shader.attach(vert);
	shader.attach(frag);
	shader.link();
	shader.use();

	glUniform1i(glGetUniformLocation(shader.get(), "environment_map"), 0);
	glUniformMatrix4fv(glGetUniformLocation(shader.get(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	int mipLevels = 5;

	for (int mip = 0; mip < mipLevels; mip++) {
		int width = 128 * std::pow(0.5, mip);
		int height = width;

		glBindRenderbuffer(GL_RENDERBUFFER, rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
		glViewport(0, 0, width, height);

		float roughness = (float) mip / (float) (mipLevels - 1);

		glUniform1f(glGetUniformLocation(shader.get(), "roughness"), roughness);

		for (int i = 0; i < 6; i++) {
			glUniformMatrix4fv(glGetUniformLocation(shader.get(), "view"), 1, GL_FALSE, glm::value_ptr(views[i]));
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, prefilter, mip);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			cube.render();
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void eyesore::Environment::makeBRDFLUT(GLuint fbo, GLuint rbo)
{
	glGenTextures(1, &brdfLUT);
	glBindTexture(GL_TEXTURE_2D, brdfLUT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, 512, 512, 0, GL_RG, GL_FLOAT, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, brdfLUT, 0);

	glViewport(0, 0, 512, 512);

	Shader vert("../shaders/brdf_convolve.vert", GL_VERTEX_SHADER);
	Shader frag("../shaders/brdf_convolve.frag", GL_FRAGMENT_SHADER);
	ShaderProgram shader;

	shader.attach(vert);
	shader.attach(frag);
	shader.link();
	shader.use();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	renderQuad();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

