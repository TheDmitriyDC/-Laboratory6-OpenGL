#pragma once
#include "GL-Linker.h"
#include "Shader.h"
#include "Transform.h"
#include "Camera.h"

#include <vector>

class Sphere : public Transform
{
private:
    // Geometry
    unsigned int VAO = 0, VBO = 0, EBO = 0;
    unsigned int IC = 0;
    std::vector<glm::vec3> positions{ 0 };
    std::vector<glm::vec2> uv{ 0 };
    std::vector<glm::vec3> normals{ 0 };
    std::vector<unsigned int> indices{ 0 };
    // --------

    // Parameters
    const unsigned int X_SEGMENTS = 16;
    const unsigned int Y_SEGMENTS = 16;
    const float PI = 3.14159265359f;
    // ----------

public:
    void Load();

    /// <summary>
    /// Draws object with given shader.
    /// </summary>
    /// <param name="camera"></param>
    /// <param name="shader"></param>
    void Draw(Camera camera, Shader shader, unsigned int fps = 24);

    /// <summary>
    /// Gathers current object's model for next frame.
    /// </summary>
    void Gather();
private:
    glm::mat4 Model()
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, Position);
        model = glm::scale(model, Scale);
        glm::mat4 rotation = glm::toMat4(Rotation);

        return model * rotation;
    }
};