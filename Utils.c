#include "Utils.h"

void ExitOnGLError(const char* error_message) {
	const GLenum ErrorValue = glGetError();

	if (ErrorValue != GL_NO_ERROR) {
		const char* APPEND_DETAIL_STRING = ": %s\n";
		const size_t APPEND_LENGTH = strlen(APPEND_DETAIL_STRING) + 1;
		const size_t message_length = strlen(error_message);
		char* display_message = (char*)malloc(message_length + APPEND_LENGTH);

		memcpy(display_message, error_message, message_length);
		memcpy(&display_message[message_length], APPEND_DETAIL_STRING, APPEND_LENGTH);

		fprintf(stderr, display_message, gluErrorString(ErrorValue));

		free(display_message);
		exit(EXIT_FAILURE);
	}
}

unsigned char* loadTexturePNG(const char* filename, int& width, int& height) {
	FILE* file = fopen(filename, "r");
	
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		printf("Could not initialize libPNG's read struct.\n");
		exit(-1);
	}
	
	png_infop png_info_ptr = png_create_info_struct(png_ptr);
	if (png_info_ptr == NULL) {
		printf("Could not initialize libPNG's info pointer.\n");
		exit(-1);
	}
	
	/* We jump back here if an error is encountered . */
	if (setjmp(png_jmpbuf(png_ptr))) {
		printf("LibPNG encountered and error.\n");
		
		png_destroy_read_struct(&png_ptr, &png_info_ptr, NULL);
		exit(-1);
	}
	
	png_init_io(png_ptr, file);
	
	png_read_png(png_ptr, png_info_ptr, 0, NULL);
	
	png_uint_32 png_width = 0;
	png_uint_32 png_height = 0;
	int bits = 0;
	int colour_type = 0;
	
	png_get_IHDR(png_ptr, png_info_ptr, &png_width, &png_height, &bits, &colour_type, NULL, NULL, NULL);
	
	const unsigned BITS_PER_BYTE = 8;
	unsigned bytes_per_colour = (unsigned)bits /BITS_PER_BYTE;
	unsigned colours_per_pixel;
	
	if (colour_type == PNG_COLOR_TYPE_RGB) {
		colours_per_pixel = 3;
	} else {
		printf("Colour types other than RGB are not supported.");
		exit(-1);
	}
	
	printf("png_width = %d, png_height = %d, bits = %d, colour type = %d.\n", (int)png_width, (int)png_height, bits, colour_type);
	
	unsigned char* data = new unsigned char[png_width * png_height * colours_per_pixel * bytes_per_colour];
	
	png_bytepp row_pointers = png_get_rows(png_ptr, png_info_ptr);
	
	unsigned index = 0;
	for (unsigned y = 0; y < png_height; y++) {
		unsigned x = 0;
		while (x < png_width * colours_per_pixel * bytes_per_colour) {
				data[index++] = row_pointers[y][x++];
				data[index++] = row_pointers[y][x++];
				data[index++] = row_pointers[y][x++];
		}
	}
	
	width = (int)png_width;
	height = (int)png_height;
	
	return data;
}

void loadTexture() {
	glActiveTexture(GL_TEXTURE0);
	unsigned textName;
	glGenTextures(1, &textName);
	glBindTexture(GL_TEXTURE_2D, textName);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	int width = 0;
	int height = 0;
		
	unsigned char* data = loadTexturePNG("heightmap.png", width, height);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	delete[] data;
}
