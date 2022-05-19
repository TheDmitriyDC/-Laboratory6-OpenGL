#include "Sphere.h"

void Sphere::Load()
{
    glGenVertexArrays(1, &VAO);

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    float xSegment = 0.0f;
    float ySegment = 0.0f;
    float xPos = 0.0f;
    float yPos = 0.0f;
    float zPos = 0.0f;
    for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
    {
        for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
        {
            xSegment = (float)x / (float)X_SEGMENTS;
            ySegment = (float)y / (float)Y_SEGMENTS;
            xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
            yPos = std::cos(ySegment * PI);
            zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);

            positions.push_back(glm::vec3(xPos, yPos, zPos));
            uv.push_back(glm::vec2(xSegment, ySegment));
            normals.push_back(glm::vec3(xPos, yPos, zPos));
        }
    }

    bool oddRow = false;
    for (unsigned int y = 0; y < Y_SEGMENTS; ++y)
    {
        if (!oddRow) // even rows: y == 0, y == 2; and so on
        {
            for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
            {
                indices.push_back(y * (X_SEGMENTS + 1) + x);
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
            }
        }
        else
        {
            for (int x = X_SEGMENTS; x >= 0; --x)
            {
                indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
                indices.push_back(y * (X_SEGMENTS + 1) + x);
            }
        }
        oddRow = !oddRow;
    }
    IC = indices.size();

    std::vector<float> data{};
    for (std::size_t i = 0; i < positions.size(); ++i)
    {
        data.push_back(positions[i].x);
        data.push_back(positions[i].y);
        data.push_back(positions[i].z);
        if (uv.size() > 0)
        {
            data.push_back(uv[i].x);
            data.push_back(uv[i].y);
        }
        if (normals.size() > 0)
        {
            data.push_back(normals[i].x);
            data.push_back(normals[i].y);
            data.push_back(normals[i].z);
        }
    }

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    float stride = (3 + 2 + 3) * sizeof(float);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(stride), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(stride), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, static_cast<GLsizei>(stride), (void*)(5 * sizeof(float)));
}

void Sphere::Draw(Camera camera, Shader shader, unsigned int fps)
{
    Current = Model();

    shader.Process();
    shader.SetMatrix4("model", Current);
    shader.SetMatrix4("view", camera.View());
    shader.SetMatrix4("projection", camera.Projection);
    shader.SetMatrix4("PP", camera.Previous);
    shader.SetMatrix4("PV", camera.PV);
    shader.SetMatrix4("PM", Previous);
    shader.SetInt("TF", 144); // Target Framerate
    shader.SetInt("CF", fps); // Current Framerate

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLE_STRIP, IC, GL_UNSIGNED_INT, 0);
}

void Sphere::Gather()
{
    Previous = Model();
}
