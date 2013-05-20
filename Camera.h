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

const float CAM_ROTATE_DAMP = 0.001f;
const float CAM_MOVE_SPEED = 5.0f/60;

class Camera : public Positionable {
	public:
		Camera(ShaderManager* shader, int width, int height, glm::vec3 position, glm::vec3 lookat) : Positionable() {
			_shader = shader;
			CurrentHeight = height;
			CurrentWidth = width;
			_translation = position;
			velocity = glm::vec3(0.0f);
			at = lookat;
			up = glm::vec3(0.0f, 1.0f, 0.0f);
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
			glm::mat4 ViewMatrix = glm::lookAt(_translation, at, up);
			glUniformMatrix4fv(_shader->getUniformLocation("view"), 1, GL_FALSE, glm::value_ptr(ViewMatrix));
			ExitOnGLError("ERROR: Could not set Uniform viewMatrix");
			
			glUseProgram(0);
		};

		void updatePerspective(int width, int height) {
			ExitOnGLError("ERROR: Messedup Before");
			glUseProgram(_shader->getShaderID());
			ExitOnGLError("ERROR: Shader is messedup");
			if (!_shader->hasUniform("projection")) {
				printf("[Warning] projection uniform not found.\n");	
				return;
			}
			CurrentWidth = width;
			CurrentHeight = height;
			glViewport(0, 0, CurrentWidth, CurrentHeight);
			//printf("Projection: %d\n", _shader->getUniformLocation("projection"));
			glm::mat4 ProjectionMatrix = glm::perspective(45.0f, (float)CurrentWidth / (float)CurrentHeight, 0.1f, 100.0f);
			glUniformMatrix4fv(_shader->getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
			ExitOnGLError("ERROR: Could not set Uniform projection");
			glUseProgram(0);
		};

		void setVelocity(glm::vec3 newVelocity) {
			velocity = newVelocity;
		};

		glm::vec3 getVelocity() {
			return velocity;
		};

		void rotate(int deltaX, int deltaY) {
			if (deltaX != 0 || deltaY != 0) {
				glm::vec3 cameraNormal = at - _translation;
				glm::vec3 right = glm::normalize(glm::cross(cameraNormal, up));

				glm::vec3 hDirection = cos(-deltaX*CAM_ROTATE_DAMP)*cameraNormal+sin(-deltaX*CAM_ROTATE_DAMP)*right;
				at = _translation + hDirection;

				cameraNormal = at - _translation;
				glm::vec3 vDirection = cos(deltaY*CAM_ROTATE_DAMP)*cameraNormal+sin(deltaY*CAM_ROTATE_DAMP)*up;
				at = _translation + glm::normalize(vDirection);
			}
		};

		void setLookAt(glm::vec3 lookAt) {
			at = lookAt;
		};

		void tick() {
			//glm::vec3 direction = glm::normalize(at - _translation);
			if (velocity.x != 0) {
				glm::vec3 delta = glm::normalize(at - _translation);
				_translation = _translation + delta*velocity.x;
				at = at +  delta*velocity.x;
			}
			if (velocity.z != 0) {
				glm::vec3 delta = glm::normalize(glm::cross(at - _translation, up));
				_translation = _translation - delta*velocity.z;
				at = at - delta*velocity.z;
			}

			//translate(velocity);
		};
	protected:
		ShaderManager* _shader;
		int CurrentWidth;
		int CurrentHeight;
		glm::vec3 velocity;
		glm::vec3 at;
		glm::vec3 up;
};

#endif