#include "FrameBuffer.h"

FrameBuffer::FrameBuffer() {
	glGenFramebuffers(1, &bufferID);
}

FrameBuffer::~FrameBuffer() {
   glDeleteFramebuffers(1, &bufferID);
}

void FrameBuffer::bind() {
   glBindFramebuffer(GL_FRAMEBUFFER, bufferID);
}

void FrameBuffer::unbind() {
   glBindFramebuffer(GL_FRAMEBUFFER, 0);
}