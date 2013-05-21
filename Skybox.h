#ifndef SKYBOX_H
#define SKYBOX_H

#include <GL/glew.h>
#include "Texture.h"
#include "Shader.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wconversion"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#pragma GCC diagnostic pop

class Skybox {
	public:
		Skybox();
		~Skybox();
		void draw();
		//void setupCubeMap(GLuint& texture);
	private:
		GLuint texture;
		GLuint indexCount;
};

#endif