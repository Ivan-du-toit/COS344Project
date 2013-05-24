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


void ColourFrameBuffer::write() {
	bind();

	const GLsizei DATA_SIZE = _width * _height * (GLsizei)sizeof(GL_UNSIGNED_BYTE) * (GLsizei)3;
	GLubyte* data = new GLubyte[(unsigned)DATA_SIZE];

	glReadPixels(0, 0, _width, _height, GL_RGBA, GL_UNSIGNED_BYTE, data);

	unsigned char* RGBdata = new unsigned char[(unsigned)_width * _height* sizeof(unsigned char) * 4];
	GLuint index = 0;
	GLuint lineWidth = _width*4;
	GLuint max = _width * _height * 4;
	GLuint offset = lineWidth;
	for (GLsizei y = 0; y < _height; y++)
	{
		for (GLsizei x = 0; x < _width; x++)
		{
			RGBdata[max - offset + index] = data[index];
			RGBdata[max - offset + index+1] = data[index+1];
			RGBdata[max - offset + index+2] = data[index+2];
			RGBdata[max - offset + index+3] = data[index+3];
			index += 4;
		}
		offset += lineWidth*2;
	}

	//Encode the image
	unsigned error = lodepng_encode32_file("AA.png", RGBdata, _width, _height);

	//if there's an error, display it
	if(error) printf("error %u: %s\n", error, lodepng_error_text(error));

	/*const GLsizei DATA_SIZE = _width * _height * (GLsizei)sizeof(GLfloat) * (GLsizei)3;
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
	if(error) printf("error %u: %s\n", error, lodepng_error_text(error));*/
}