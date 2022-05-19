#pragma once
#include "GL-Linker.h"
#include "GLM-Linker.h"
#include "Transform.h"

class Camera : public Transform
{
public:
    // constructor with vectors
    Camera();
    ~Camera();
public:
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 624.0f / 480.0f, 1.0f, 400.0f);
    glm::vec3 Front = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 Right = glm::vec3(1.0f, 0.0f, 0.0f);

    glm::mat4 Previous = glm::perspective(glm::radians(45.0f), 624.0f / 480.0f, 1.0f, 400.0f);
    glm::mat4 PV = glm::mat4(0.0f);

    float FOV = 90.0f;
public:
    /// <summary>
    /// View-matrix.
    /// </summary>
    /// <returns> Camera view-matrix. </returns>
    glm::mat4 View();
    /// <summary>
    /// Gathers camera projection and view for next frame.
    /// </summary>
    void Gather();
};