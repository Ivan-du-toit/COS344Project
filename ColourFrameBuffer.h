#ifndef COLOURFRAMEBUFFER_H
#define COLOURFRAMEBUFFER_H

#include <cstdio>

#include "FrameBuffer.h"

class ColourFrameBuffer: public FrameBuffer {
	public:
		ColourFrameBuffer(GLuint width, GLuint height);
	protected:
		GLuint _width;
		GLuint _height;
};

#endif