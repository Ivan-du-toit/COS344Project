#include "LoadedMesh.h"

LoadedMesh::LoadedMesh(const char* filename, ShaderManager* shader) : Mesh(shader) {
	_filename = filename;
	myVOAID = createVOA();
}

LoadedMesh::~LoadedMesh() {
	glDeleteBuffers(2, &BufferIds[0]);
	glDeleteVertexArrays(1, &myVOAID);
	ExitOnGLError("ERROR: Could not destroy the buffer objects");
}

GLuint LoadedMesh::createVOA() {
	std::vector<GLuint> vertexIndices, uvIndices, normalIndices;
	std::vector<GLfloat> vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<GLfloat> normals;

	FILE * file = fopen(_filename, "r");
	if( file == NULL ){
		printf("Impossible to open the file !\n");
		return false;
	}

	while( 1 ) {
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF.
		if ( strcmp( lineHeader, "v" ) == 0 ) {
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			vertices.push_back(vertex.x);
			vertices.push_back(vertex.y);
			vertices.push_back(vertex.z);
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			normals.push_back(normal.x);
			normals.push_back(normal.y);
			normals.push_back(normal.z);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			unsigned int vertexIndex[3], normalIndex[3];

			//This is only a basic parser
			int matches = fscanf(file, " %d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
			if (matches != 6){
				printf("File can't be read by parser");
				return -1;
			}

			vertexIndices.push_back(vertexIndex[0]-1);
			vertexIndices.push_back(vertexIndex[1]-1);
			vertexIndices.push_back(vertexIndex[2]-1);
			normalIndices.push_back(normalIndex[0]-1);
			normalIndices.push_back(normalIndex[1]-1);
			normalIndices.push_back(normalIndex[2]-1); 
		}

	}

	glGenVertexArrays(1, &myVOAID);
	
	ExitOnGLError("ERROR: Could not generate the VAO");
	
	glBindVertexArray(myVOAID);
	ExitOnGLError("ERROR: Could not bind the VAO");

	GLuint positionLoc = getAttributeLocation("position");
	GLuint colourLoc = getAttributeLocation("colour");
	GLuint normalLoc = getAttributeLocation("normal");

	//printf("normal: %d\n", normalLoc);
	glEnableVertexAttribArray(positionLoc);
	glEnableVertexAttribArray(colourLoc);
	//glEnableVertexAttribArray(normalLoc);
	ExitOnGLError("ERROR: Could not enable vertex attributes");

	glGenBuffers(2, &BufferIds[0]);
	ExitOnGLError("ERROR: Could not generate the buffer objects");

	glBindBuffer(GL_ARRAY_BUFFER, BufferIds[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(GLfloat), &vertices, GL_STATIC_DRAW);
	ExitOnGLError("ERROR: Could not bind the VBO to the VAO");

	glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 3*sizeof(vertices[0]), (GLvoid*)0);
	glVertexAttribPointer(colourLoc, 3, GL_FLOAT, GL_FALSE, 3*sizeof(vertices[0]), (GLvoid*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferIds[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size()*sizeof(GLuint), &vertexIndices, GL_STATIC_DRAW);
	ExitOnGLError("ERROR: Could not bind the IBO to the VAO");
			
	/*glBindBuffer(GL_ARRAY_BUFFER, BufferIds[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);
	ExitOnGLError("ERROR: Could not bind the VBO to the VAO");

	glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 3*sizeof(VERTICES[0]), (GLvoid*)0);
	ExitOnGLError("ERROR: Could not set VAO attributes");*/


	indexCount = vertexIndices.size();
	return myVOAID;
};