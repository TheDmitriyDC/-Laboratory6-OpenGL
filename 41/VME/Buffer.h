#pragma once
#include "GL-Linker.h"
#include "Shader.h"

#include "Camera.h"

#include <string>

class Buffer
{
public:
    /// <summary>
    /// Framebuffer object.
    /// </summary>
    unsigned int FBO = 0;
    /// <summary>
    /// Texture attachment.
    /// </summary>
    unsigned int Texture = 0;
    /// <summary>
    /// Renderbuffer object.
    /// </summary>
    unsigned int RBO = 0;
public:
    /// <summary>
    /// Buffer's shader.
    /// </summary>
    Shader Shader = NULL;
public:
    /// <summary>
    /// Loads shader.
    /// </summary>
    /// <param name="vertexPath"></param>
    /// <param name="fragmentPath"></param>
    void Load(const char* vertexPath, const char* fragmentPath);
    /// <summary>
    /// Binds textures to shader.
    /// </summary>
    void Setup();
    /// <summary>
    /// Initializes framebuffer and texture.
    /// </summary>
    virtual void Initialize();

    /// <summary>
    /// Binds framebuffer and activates shader.
    /// </summary>
    virtual void Bind();
};