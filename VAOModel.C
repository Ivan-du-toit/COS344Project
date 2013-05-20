#include "VAOModel.h"

VAOModel::VAOModel(ShaderManager* shader, Mesh* mesh) : Model(shader, mesh){ }

VAOModel::~VAOModel() {
	glDeleteVertexArrays(1, &(_mesh->myVOAID));
}

void VAOModel::bind() {
	glBindVertexArray(_mesh->getVOAID());
}

void VAOModel::drawVOA() {
	ExitOnGLError("Before mesh");
	glPatchParameteri(GL_PATCH_VERTICES, 3);
	glDrawArrays(GL_TRIANGLES, 0, _mesh->getIndexCount());
	ExitOnGLError("Could not draw mesh");
}