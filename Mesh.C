#include "Mesh.h"

/*GLuint Mesh::myVOAID = -1;
int Mesh::indexCount = -1;*/

Mesh::Mesh(ShaderManager* shader) {
	_shader = shader;
}

Mesh::~Mesh() {

}

GLuint Mesh::getIndexCount() {
	//printf("123\n");
	return indexCount;
}

GLuint Mesh::getVOAID() {
	return myVOAID;
}

GLuint Mesh::getAttributeLocation(const char* name) {
	GLint location = _shader->getAtrributeLocation(name);

	if (location == -1)	{
		fprintf(stderr, "[WARNING] Could not find attribute '%s'.\n", name);
	}

	return (GLuint)location;
}