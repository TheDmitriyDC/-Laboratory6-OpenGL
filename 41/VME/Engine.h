#pragma once
#include "Window.h"
#include "Scene.h"
#include "Time.h"

#include "Utilities.h"

#pragma region Buffers
#include "Buffer.h"
#include "Velocity.h"
#include "GBO.h"
#pragma endregion
#include <iostream>
class Engine
{
public:
	Engine();
	/// <summary>
	/// Main application loop, also some initialization.
	/// </summary>
	/// <param name="hInstance"></param>
	/// <param name="hPrevInstance"></param>
	/// <param name="lpCmdLine"></param>
	/// <param name="nCmdShow"></param>
	/// <returns></returns>
	int Process(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT nCmdShow);
	/// <summary>
	/// Configures OpenGL, enables capabilities.
	/// </summary>
	void Configure();
	~Engine();
private:
	Window WND;
	Camera camera;
	Scene scene;
	Time time;

	Shader DF; // Default Shader

	#pragma region Buffers
		Buffer IB; // Input Buffer
		Velocity VB; // Velocity Buffer
		Buffer MB; // Motion-Blur
		GBO GB; // Geometry-Buffer
	#pragma endregion
private:
	float QV[24] =
	{
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	unsigned int QVAO = 0;
	unsigned int QVBO = 0;
};