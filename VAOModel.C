#include "VAOModel.h"

VAOModel::VAOModel(ShaderManager* shader, Mesh* mesh) : Model(shader, mesh){ }

VAOModel::~VAOModel() {
	
}

void VAOModel::drawVOA() {
	glDeleteVertexArrays(1, &(_mesh->myVOAID));
}