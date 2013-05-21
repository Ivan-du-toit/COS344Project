#include "ColourFrameBuffer.h"

ColourFrameBuffer::ColourFrameBuffer(GLuint width, GLuint height): FrameBuffer(), _width(width), _height(height) {
	glActiveTexture(GL_TEXTURE0);

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_FLOAT, 0);

	bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	GLuint status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE) {
		switch (status) {
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
				printf("Error: Incomplete framebuffer attachment.");
			break;
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
				printf("Error: No color attachment in draw buffer.");
			break;
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
	            printf("Error: No color attachment in read buffer.");
			break;
		    case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			    printf("Error: Framebuffer is missing an attachment.");
			break;
			case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
				printf("Error: The framebuffer different size multisamples.");
			break;
			case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
	            printf("Error: Not all framebuffer attachments are layered.");
			break;
		    case GL_FRAMEBUFFER_UNSUPPORTED:
			    printf("Error: The framebuffer configuration is unsupported.");
			break;
			default:
				//cout << status << endl;
				printf("Error: Unknown framebuffer error.");
		}
	}
}