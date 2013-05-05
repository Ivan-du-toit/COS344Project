#ifndef PLAIN_MODEL_H
#define PLAIN_MODEL_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Model.h"
#include "Utils.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wconversion"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#pragma GCC diagnostic pop

class PlainModel : public Model{
  public:
    PlainModel(ShaderManager* shader, Mesh* mesh) : Model(shader, mesh){ };
	virtual ~PlainModel(){};
  protected: 
    //virtual void createVOA();
	virtual void drawVOA() {
		if (_shader->hasUniform("tessLevel")) {
			glUniform1f(_shader->getUniformLocation("tessLevel"), 1);
			ExitOnGLError("ERROR: Could not set the shader uniforms");
		}

		glPatchParameteri(GL_PATCH_VERTICES, 3);
		glDrawElements(GL_PATCHES, _mesh->getIndexCount(), GL_UNSIGNED_INT , 0);
		ExitOnGLError("ERROR: Could not draw the cube");
	};
  private:
};

#endif