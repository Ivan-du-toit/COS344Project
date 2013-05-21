#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Camera.h"

class Light : public Camera {
	public:
		Light(ShaderManager* shader, int width, int height, glm::vec3 position, glm::vec3 lookat) : Camera(shader, width, height, position, lookat) {
		};
};

#endif