#pragma once
#include "GLM-Linker.h"
#include <string>

/// <summary>
/// Basic transform class.
/// </summary>
class Transform
{
public:
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Scale = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::quat Rotation = glm::quat(0.0f, 0.0f, 0.0f, 0.0f);

	glm::mat4 Current = glm::mat4(0.0f); // Current frame matrix.
	glm::mat4 Previous = glm::mat4(0.0f); // Previous frame matrix.
};