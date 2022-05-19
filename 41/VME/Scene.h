#pragma once
#include "Camera.h"
#include "Sphere.h"
#include <chrono>

class Scene
{
public:
	Scene();

	/// <summary>
	/// Initializes scene, loads objects.
	/// </summary>
	void Initialize();

	/// <summary>
	/// Updates scene.
	/// </summary>
	/// <param name="dt"></param>
	void Update(float dt);

	/// <summary>
	/// Renders every object in scene with given object.
	/// </summary>
	/// <param name="camera"></param>
	/// <param name="shader"></param>
	/// <param name="fps"></param>
	void Render(Camera camera, Shader shader, int fps = 24);

	/// <summary>
	/// Gathers information for next frame.
	/// </summary>
	void Gather();

	~Scene();
public:
	Sphere sphere;
};