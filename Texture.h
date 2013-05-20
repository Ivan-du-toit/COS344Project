#ifndef TEXTURE_H
#define TEXTURE_H

#include "Utils.h"
#include "CImg.h"

using namespace cimg_library; 

class Texture {
	public:
		Texture(const char* filename);
		void activate();
		GLint getTexID();
	protected:
		int width;
		int height;
		GLuint texID;
};

#endif

