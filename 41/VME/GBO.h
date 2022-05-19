#pragma once
#include "GL-Linker.h"
#include "Shader.h"

#include "Camera.h"

#include <string>

/// <summary>
/// Multiple Render Targets Geometry-Buffer.
/// </summary>
class GBO
{
public:
    unsigned int FBO = 0;
    unsigned int Position = 0;
    unsigned int Normal = 0;
    unsigned int RBO = 0;
public:
    Shader Shader = NULL;
public:
    /// <summary>
    /// Loads shader.
    /// </summary>
    void Load();
    /// <summary>
    /// Initializes framebuffer and textures.
    /// </summary>
    void Initialize();
    /// <summary>
    /// Binds framebuffer, clears texture and activates shader.
    /// </summary>
    /// <param name="camera"></param>
    void Bind(Camera camera);
};