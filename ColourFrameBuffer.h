#ifndef COLOURFRAMEBUFFER_H
#define COLOURFRAMEBUFFER_H

#include <cstdio>

#include "FrameBuffer.h"
#include "lodepng.h"

class ColourFrameBuffer: public FrameBuffer {
	public:
		ColourFrameBuffer(GLuint width, GLuint height);
		void write();
	protected:
		GLuint _width;
		GLuint _height;
};

#endif