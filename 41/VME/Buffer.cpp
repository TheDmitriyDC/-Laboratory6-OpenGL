#include "Buffer.h"

void Buffer::Load(const char* vertexPath, const char* fragmentPath)
{
	Shader.Load(vertexPath, fragmentPath);
}

void Buffer::Setup()
{
	Shader.Process();
	Shader.SetInt("screenTexture", 0);
	Shader.SetInt("screenVelocity", 4);
}

void Buffer::Initialize()
{
    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glGenTextures(1, &Texture);
    glBindTexture(GL_TEXTURE_2D, Texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 624, 480, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Texture, 0);

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 624, 480);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RBO);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        OutputDebugStringA("Framebuffer could not be completed!\n");
    }
}

void Buffer::Bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
    Shader.Process();
}
