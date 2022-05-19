#include "Scene.h"

Scene::Scene() {}

void Scene::Initialize()
{
	sphere.Load();
	sphere.Position = glm::vec3(0.0f, 0.0f, 12.0f);
}

void Scene::Update(float dt)
{
	if (sphere.Position.x > 8.0f)
	{
		sphere.Position.x -= 16.0f;
	}
	sphere.Position.x += sin(dt * 16.0f);
}

void Scene::Render(Camera camera, Shader shader, int fps)
{
	sphere.Draw(camera, shader, fps);
}

void Scene::Gather()
{
	sphere.Gather();
}

Scene::~Scene() {}