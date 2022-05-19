#pragma once
#include "GL-Linker.h"
#include "GLM-Linker.h"

#include <string>
#include <fstream>
#include <sstream>

class Shader
{
private:
    unsigned int ID = 0;
public:
    Shader(const char* vertexPath = nullptr, const char* fragmentPath = nullptr, const char* geometryPath = nullptr);
    void Load(const char* vertexPath = nullptr, const char* fragmentPath = nullptr, const char* geometryPath = nullptr);
    void Process();
    ~Shader();
public:
    //Setters
    void SetBool(const std::string& name, bool value) const;
    void SetInt(const std::string& name, int value) const;
    void SetFloat(const std::string& name, float value) const;
    void SetVector2(const std::string& name, const glm::vec2& value) const;
    void SetVector2(const std::string& name, float x, float y) const;
    void SetVector3(const std::string& name, const glm::vec3& value) const;
    void SetVector3(const std::string& name, float x, float y, float z) const;
    void SetVector4(const std::string& name, const glm::vec4& value) const;
    void SetVector4(const std::string& name, float x, float y, float z, float w);
    void SetMatrix2(const std::string& name, const glm::mat2& mat) const;
    void SetMatrix3(const std::string& name, const glm::mat3& mat) const;
    void SetMatrix4(const std::string& name, const glm::mat4& mat) const;
};