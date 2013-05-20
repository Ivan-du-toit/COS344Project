#ifndef TEXTURE_H
#define TEXTURE_H

#include "Utils.h"
#include "CImg.h"

using namespace cimg_library; 

class Texture {
	public:
		Texture(const char* filename);
		~Texture();
		void activate();
		GLint getTexID();

		int getWidth();
		int getHeight();
		unsigned char* getColours();
	protected:
		int width;
		int height;
		GLuint texID;
		unsigned char* data;
};

#endif

