#ifndef TEXTURE_H
#define TEXTURE_H

#include "Mesh.h"
#include "Utils.h"

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

