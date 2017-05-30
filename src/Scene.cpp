#include <fstream>
#include <iostream>

#include "Scene.h"

using namespace eyesore;

using std::string;
using std::ifstream;
using std::cout;
using std::endl;

eyesore::Scene::Scene(string path, Camera *camera): camera(camera)
{
	GLint viewport[4];

	glGetIntegerv(GL_VIEWPORT,  viewport);

	width = viewport[2];
	height = viewport[3];

	Shader vert("../shaders/vert.glsl", GL_VERTEX_SHADER);
	Shader frag("../shaders/frag.glsl", GL_FRAGMENT_SHADER);

	shader.attach(vert);
	shader.attach(frag);
	shader.link();
	shader.use();

	ifstream file(path);
	string line;

	while (getline(file, line)) {
		auto i = line.find(" ");
		string type = line.substr(0, i);

		if (type == "MODEL")
			models.push_back(Model(line.substr(i + 1)));
		else if (type == "ENV")
			environment = new Environment(line.substr(i + 1), camera);
	}
}

void eyesore::Scene::add(Model model)
{
	models.push_back(model);
}

void eyesore::Scene::render()
{
	glViewport(0, 0, width, height);

	shader.use();
	environment->use();

	for (Model &model : models)
		model.render(*camera);

	environment->render();
}

