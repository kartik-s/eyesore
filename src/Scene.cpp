#include "Scene.h"

using namespace eyesore;

void eyesore::Scene::add(Model model)
{
	models.push_back(model);
}

void eyesore::Scene::render(Camera &camera) const
{
	for (const Model &model : models)
		model.render(camera);
}

