#ifndef DEPTHBUFFER_H
#define DEPTHBUFFER_H

#include <GL/glew.h>
#include <cstdio>

#include "FrameBuffer.h"

class DepthBuffer : public FrameBuffer {
	public:
		DepthBuffer(GLuint width, GLuint height);
	protected:
		GLuint _width;
		GLuint _height;
};

#endif