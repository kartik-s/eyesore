#include "Scene.h"

using namespace eyesore;

eyesore::Scene::Scene(Camera camera): camera(camera)
{

}

void eyesore::Scene::add(Model model)
{
	models.push_back(model);
}

void eyesore::Scene::render() const
{
	for (const Model &model : models)
		model.render();
}

