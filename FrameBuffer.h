#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <GL/glew.h>

class FrameBuffer {
	public:
		FrameBuffer();
		~FrameBuffer();
		void bind();
		void unbind();
	protected:
		GLuint bufferID;
};

#endif