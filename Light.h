#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Camera.h"

class Light : public Camera {
	public:
		Light(ShaderManager* shader, int width, int height, glm::vec3 position, glm::vec3 lookat) : Camera(shader, width, height, position, lookat) {
		};
		void updateView(ShaderManager* shader) {
			_shader = shader;
			updatePerspective(CurrentWidth, CurrentHeight);

			glUseProgram(_shader->getShaderID());
			glm::mat4 ViewMatrix = glm::lookAt(_translation, at, up);
			glUniformMatrix4fv(_shader->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(ViewMatrix));
			ExitOnGLError("ERROR: Could not set Uniform viewMatrix");
			
			glUseProgram(0);
		};
};

#endif