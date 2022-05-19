#pragma once
#include "GL-Linker.h"

class Utilities
{
public:
	static void Bufferize(unsigned int VAO, unsigned int Texture)
	{
		glBindVertexArray(VAO);
		glBindTexture(GL_TEXTURE_2D, Texture);
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	template <typename T>
	static void Combine(T FB1, T FB2)
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, FB1);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FB2);
		glBlitFramebuffer(0, 0, 624, 480, 0, 0, 624, 480, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST);
	}
};