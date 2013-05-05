#include "Sphere.h"

Sphere::Sphere(ShaderManager* shader, Mesh* mesh) : Model(shader, mesh){ }

Sphere::~Sphere() {
	
}

void Sphere::drawVOA() {
	if (_shader->hasUniform("tessLevel")) {
		glUniform1f(_shader->getUniformLocation("tessLevel"), 15);
		ExitOnGLError("ERROR: Could not set the shader uniforms1");
	}

	/*if (_shader->hasUniform("ligthPos")) {
		glUniform3fv(_shader->getUniformLocation("ligthPos"), glm::value_ptr(glm::vec3(5.0f)));
		ExitOnGLError("ERROR: Could not set the shader uniforms1");
	}*/
	
	glPatchParameteri(GL_PATCH_VERTICES, 3);
	//glDrawElements(GL_PATCHES, number_indices, GL_UNSIGNED_INT , 0);
	glDrawElements(GL_PATCHES, _mesh->getIndexCount(), GL_UNSIGNED_INT , 0);
	ExitOnGLError("ERROR: Could not draw the cube");
}