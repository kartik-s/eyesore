#include <glm/glm.hpp>

#include "eyesore.h"
#include "Scene.h"
#include "Model.h"

using namespace eyesore;
using namespace glm;

int main(void)
{
	Camera c(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, -1.0f), 4.0f/3.0f);
	Engine e(c);
	Scene s;

	e.makeWindow(400, 300, "eyesore", false);
	s.add(Model("../models/teapot.obj"));
	e.setScene(s);
	e.run();

	return 0;
}

