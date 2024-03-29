#include "DepthBuffer.h"

#include "lodepng.h"

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
	//glDrawBuffer(GL_NONE);
	//glReadBuffer(GL_NONE);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture, 0);

	GLuint status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

	if (status != GL_FRAMEBUFFER_COMPLETE) {
		switch (status) {
			case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
				printf("Error: Incomplete framebuffer attachment.\n");
			break;
			case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
				printf("Error: No color attachment in draw buffer.\n");
			break;
			case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
	            printf("Error: No color attachment in read buffer.\n");
			break;
		     case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
			    printf("Error: Framebuffer is missing an attachment.\n");
			break;
			case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
				printf("Error: The framebuffer different size multisamples.\n");
			break;
			case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
				printf("Error: Not all framebuffer attachments are layered.\n");
			break;
			case GL_FRAMEBUFFER_UNSUPPORTED:
	            printf("The framebuffer configuration is unsupported.\n");
			break;
		    default:
				printf("Unknown framebuffer error.\n");
		}
	}
}

void DepthBuffer::write() {
	bind();
	const GLsizei DATA_SIZE = _width * _height * (GLsizei)sizeof(GLfloat) * (GLsizei)3;
	GLfloat* data = new GLfloat[(unsigned)DATA_SIZE];

	glReadPixels(0, 0, _width, _height, GL_DEPTH_COMPONENT, GL_FLOAT, data);
	printf("What?\n");
	unsigned char* RGBdata = new unsigned char[(unsigned)_width * _height * sizeof(unsigned char) * 4];
	GLuint index = 0;
	GLuint index2 = 0;
	GLuint pixels = _width * _height * 3;
	while (index2 < pixels) {
		RGBdata[index++] = data[index2++]*255;
		RGBdata[index++] = data[index2++]*255;
		RGBdata[index++] = data[index2++]*255;
		RGBdata[index++] = 255;
	}
	//Encode the image
	unsigned error = lodepng_encode32_file("depth.png", RGBdata, _width, _height);

	//if there's an error, display it
	if(error) printf("error %u: %s\n", error, lodepng_error_text(error));
}