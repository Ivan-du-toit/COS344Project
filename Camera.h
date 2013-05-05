#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Positionable.h"
#include "Shader.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wconversion"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#pragma GCC diagnostic pop

class Camera : public Positionable {
	public:
		Camera(ShaderManager* shader, int width, int height) : Positionable() {
			_shader = shader;
			CurrentHeight = height;
			CurrentWidth = width;
			_translation = glm::vec3(0,0,5);
		};

		void updateView() {
			updateView(_shader);
		};

		void updateView(ShaderManager* shader) {
			if (_shader != shader) {
				_shader = shader;
				updatePerspective(CurrentWidth, CurrentHeight);
			}
			glUseProgram(_shader->getShaderID());
			glm::mat4 ViewMatrix = glm::lookAt(_translation, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(_shader->getUniformLocation("worldView"), 1, GL_FALSE, glm::value_ptr(ViewMatrix));
			ExitOnGLError("ERROR: Could not set Uniform viewMatrix");
			
			glUseProgram(0);
		};

		void updatePerspective(int width, int height) {
			glUseProgram(_shader->getShaderID());
			CurrentWidth = width;
			CurrentHeight = height;
			glViewport(0, 0, CurrentWidth, CurrentHeight);
			glm::mat4 ProjectionMatrix = glm::perspective(45.0f, (float)CurrentWidth / (float)CurrentHeight, 0.1f, 100.0f);
			glUniformMatrix4fv(_shader->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
			ExitOnGLError("ERROR: Could not set Uniform projection");
			glUseProgram(0);
		};
	protected:
		ShaderManager* _shader;
		int CurrentWidth;
		int CurrentHeight;
};

#endif