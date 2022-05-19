#include "GBO.h"

void GBO::Load()
{
    Shader.Load("Shaders\\Geometry-Buffer.vert", "Shaders\\Geometry-Buffer.frag");
}

void GBO::Initialize()
{
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    // POSITION
    glGenTextures(1, &Position);
    glBindTexture(GL_TEXTURE_2D, Position);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 624, 480, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Position, 0);

    // NORMAL
    glGenTextures(1, &Normal);
    glBindTexture(GL_TEXTURE_2D, Normal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 624, 480, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, Normal, 0);

    unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    glDrawBuffers(2, attachments);

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 624, 480);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        OutputDebugStringA("Geometry-Pass buffer could not be completed!\n");
    }
}

void GBO::Bind(Camera camera)
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Shader.Process();
    Shader.SetMatrix4("projection", camera.Projection);
    Shader.SetMatrix4("view", camera.View());
}