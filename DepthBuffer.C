#include "DepthBuffer.h"

DepthBuffer::DepthBuffer(GLuint width, GLuint height) : FrameBuffer(), _height(height), _width(width) {
	glActiveTexture(GL_TEXTURE0);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, _width, _height, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);

	GLuint status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE) {
		switch (status) {
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
				printf("Error: Incomplete framebuffer attachment.");
			break;
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
				printf("No color attachment in draw buffer.");
			break;
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
	            printf("No color attachment in read buffer.");
			break;
		     case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			    printf("Framebuffer is missing an attachment.");
			break;
			case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
				printf("The framebuffer different size multisamples.");
			break;
			case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
				printf("Not all framebuffer attachments are layered.");
			break;
			case GL_FRAMEBUFFER_UNSUPPORTED:
	            printf("The framebuffer configuration is unsupported.");
			break;
		    default:
				printf("Unknown framebuffer error.");
		}
	}
}