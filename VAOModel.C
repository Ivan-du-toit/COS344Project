#include "VAOModel.h"

VAOModel::VAOModel(ShaderManager* shader, Mesh* mesh) : Model(shader, mesh){ }

VAOModel::~VAOModel() {
	glDeleteVertexArrays(1, &(_mesh->myVOAID));
}

void VAOModel::drawVOA() {
	glBindVertexArray(_mesh->getVOAID());
	glDrawArrays(GL_TRIANGLES, 0, 6);
}