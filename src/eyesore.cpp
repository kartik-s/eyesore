#include "eyesore.h"
#include "Scene.h"
#include "Model.h"

#include <glm/glm.hpp>

using namespace std;
using namespace eyesore;
using namespace glm;

int main(int argc, char **argv)
{
	Camera *c = new Camera(vec3(-50.0f, 0.0f, 0.0f), 8.0f/5.0f);
	Engine e(c);

	e.makeWindow(1366, 768, "eyesore", true);
	Scene s("../scenes/test.scene", c);
	e.run(s);

	delete c;

	return 0;
}

