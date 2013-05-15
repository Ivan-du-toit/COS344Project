#include "VAOModel.h"

VAOModel::VAOModel(ShaderManager* shader, Mesh* mesh) : Model(shader, mesh){ }

VAOModel::~VAOModel() {
	glDeleteVertexArrays(1, &(_mesh->myVOAID));
}

void VAOModel::bind() {
	glBindVertexArray(_mesh->getVOAID());
}

void VAOModel::drawVOA() {
	glDrawArrays(GL_TRIANGLES, 0, _mesh->getIndexCount());
}