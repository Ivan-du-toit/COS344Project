#include "Quad.h"

Quad::Quad(ShaderManager* shader): Mesh(shader) {
	glGenVertexArrays(1, &myVOAID);
	int _vertexCount = indexCount = 6;
   
	GLfloat* positions = new float[_vertexCount * 3];
	GLfloat* normals = new float[_vertexCount * 3];
    int index = -1;

    positions[index + 1] = -.5f;
    positions[index + 2] = .0f;
    positions[index + 3] = .5f;
    index += 3;

    positions[index + 1] = .5f;
    positions[index + 2] = .0f;
    positions[index + 3] = .5f;
    index += 3;

    positions[index + 1] = -.5f;
    positions[index + 2] = .0f;
    positions[index + 3] = -.5f;
    index += 3;

    positions[index + 1] = -.5f;
    positions[index + 2] = .0f;
    positions[index + 3] = -.5f;
    index += 3;

    positions[index + 1] = .5f;
    positions[index + 2] = .0f;
    positions[index + 3] = .5f;
    index += 3;

    positions[index + 1] = .5f;
    positions[index + 2] = .0f;
    positions[index + 3] = -.5f;

	for (int i = 0; i < _vertexCount; i++) {
		int index = i * 3;
		normals[index + 1] = 0.0f;
		normals[index + 2] = 1.0f;
		normals[index + 3] = 0.0f;
	}

	const GLsizei VERTEX_ARRAY_SIZE = _vertexCount * 3 * (GLsizei)sizeof(float);
	
	glBindVertexArray(myVOAID);
	GLuint buffers[2];
	glGenBuffers(2, buffers);
	if (shader->hasAttribute("position")) {
		glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
		glBufferData(GL_ARRAY_BUFFER, VERTEX_ARRAY_SIZE, positions, GL_STATIC_DRAW);

	
		GLuint positionLocation = shader->findAttributeLoc("position");
		glEnableVertexAttribArray(positionLocation);
		glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
	} else
		printf("[Warning] Position attribute not found.\n");

	if (shader->hasAttribute("normal")) {
		glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
		glBufferData(GL_ARRAY_BUFFER, VERTEX_ARRAY_SIZE, normals, GL_STATIC_DRAW);

		GLuint normalLocation = shader->findAttributeLoc("normal");
		glEnableVertexAttribArray(normalLocation);
		glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
	} else
		printf("[Warning] Normal attribute not found.\n");
	delete[] positions;
}

