#include "LoadedMesh.h"

LoadedMesh::LoadedMesh(const char* filename, ShaderManager* shader) : Mesh(shader) {
	_filename = filename;
	myVOAID = createVOA();
}

LoadedMesh::~LoadedMesh() {
	glDeleteBuffers(4, &BufferIds[0]);
	glDeleteVertexArrays(1, &myVOAID);
	ExitOnGLError("ERROR: Could not destroy the buffer objects");
}

GLuint LoadedMesh::createVOA() {
	glGenVertexArrays(1, &myVOAID);
	ExitOnGLError("ERROR: Could not generate the VAO");
	
	glBindVertexArray(myVOAID);
	ExitOnGLError("ERROR: Could not bind the VAO");

	// Read our .obj file
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> uvs;
    std::vector<glm::vec3> normals;
    bool res = loadOBJ("suzanne.obj", vertices, uvs, normals);

    std::vector<unsigned short> indices;
    std::vector<glm::vec3> indexed_vertices;
    std::vector<glm::vec2> indexed_uvs;
    std::vector<glm::vec3> indexed_normals;
    indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);

    // Load it into a VBO

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_vertices.size() * sizeof(glm::vec3), &indexed_vertices[0], GL_STATIC_DRAW);
	indexCount = indexed_vertices.size()*3;
    GLuint uvbuffer;
    glGenBuffers(1, &uvbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_uvs.size() * sizeof(glm::vec2), &indexed_uvs[0], GL_STATIC_DRAW);

    GLuint normalbuffer;
    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, indexed_normals.size() * sizeof(glm::vec3), &indexed_normals[0], GL_STATIC_DRAW);

    // Generate a buffer for the indices as well
    GLuint elementbuffer;
    glGenBuffers(1, &elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0] , GL_STATIC_DRAW);


	//// Read our .obj file
	///*std::vector< glm::vec3> vertices;
	//std::vector< glm::vec2> uvs;
	//std::vector< glm::vec3> normals; // Won't be used at the moment.
	//bool res = loadOBJ("meshes/cube.obj", vertices, uvs, normals);

	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);*/

	//std::vector<GLuint> vertexIndices, uvIndices, normalIndices;
	//std::vector<GLfloat> vertices;
	//std::vector<glm::vec2> temp_uvs;
	//std::vector<GLfloat> normals;

	//FILE * file = fopen(_filename, "r");
	//if( file == NULL ){
	//	printf("Impossible to open the file !\n");
	//	return false;
	//}

	//while( 1 ) {
	//	char lineHeader[128];
	//	int res = fscanf(file, "%s", lineHeader);
	//	if (res == EOF)
	//		break; // EOF.
	//	if ( strcmp( lineHeader, "v" ) == 0 ) {
	//		glm::vec3 vertex;
	//		fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
	//		vertices.push_back(vertex.x);
	//		vertices.push_back(vertex.y);
	//		vertices.push_back(vertex.z);
	//	}else if ( strcmp( lineHeader, "vn" ) == 0 ){
	//		glm::vec3 normal;
	//		fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
	//		normals.push_back(normal.x);
	//		normals.push_back(normal.y);
	//		normals.push_back(normal.z);
	//	}else if ( strcmp( lineHeader, "f" ) == 0 ){
	//		unsigned int vertexIndex[3], normalIndex[3];

	//		//This is only a basic parser
	//		int matches = fscanf(file, " %d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
	//		if (matches != 6){
	//			printf("File can't be read by parser");
	//			return -1;
	//		}

	//		vertexIndices.push_back(vertexIndex[0]-1);
	//		vertexIndices.push_back(vertexIndex[1]-1);
	//		vertexIndices.push_back(vertexIndex[2]-1);
	//		normalIndices.push_back(normalIndex[0]-1);
	//		normalIndices.push_back(normalIndex[1]-1);
	//		normalIndices.push_back(normalIndex[2]-1); 
	//	}
	//	
	//}

	//glGenVertexArrays(1, &myVOAID);
	//ExitOnGLError("ERROR: Could not generate the VAO");
	//
	//glBindVertexArray(myVOAID);
	//ExitOnGLError("ERROR: Could not bind the VAO");

	//GLint positionLoc = getAttributeLocation("position");
	//GLint colourLoc = getAttributeLocation("colour");
	//GLint normalLoc = getAttributeLocation("normal");

	//glEnableVertexAttribArray(positionLoc);
	//ExitOnGLError("ERROR: Could not enable vertex attributes");

	//glGenBuffers(2, &BufferIds[0]);
	//ExitOnGLError("ERROR: Could not generate the buffer objects");

	//glBindBuffer(GL_ARRAY_BUFFER, BufferIds[0]);
	//glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vertices), &vertices[0], GL_STATIC_DRAW);
	//ExitOnGLError("ERROR: Could not bind the VBO to the VAO");

	//glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 3*sizeof(vertices[0]), (GLvoid*)0);
	//if (colourLoc != -1) {
	//	glEnableVertexAttribArray(colourLoc);
	//	glVertexAttribPointer(colourLoc, 3, GL_FLOAT, GL_FALSE, 3*sizeof(vertices[0]), (GLvoid*)0);
	//}

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferIds[1]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size()*sizeof(vertexIndices[0]), &vertexIndices[0], GL_STATIC_DRAW);
	//ExitOnGLError("ERROR: Could not bind the IBO to the VAO");

	///*GLuint normalbuffer[2];
	//glGenBuffers(2, &normalbuffer[0]);
	//glBindBuffer(GL_ARRAY_BUFFER, normalbuffer[0]);
	//glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);

	//// 3rd attribute buffer : normals
	//glEnableVertexAttribArray(normalLoc);
	//glBindBuffer(GL_ARRAY_BUFFER, normalbuffer[0]);
	//glVertexAttribPointer(normalLoc, 3,	GL_FLOAT, GL_FALSE,	0, (void*)0);*/

	//std::vector< glm::vec3> temp_normals;
	//for( unsigned int i=0; i<normalIndices.size(); i++ ){
	//	
	//}
	//GLuint normalbuffer[2];
	//glGenBuffers(2, &normalbuffer[0]);
	//glBindBuffer(GL_ARRAY_BUFFER, normalbuffer[0]);
	//glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(normals[0]), &normals[0], GL_STATIC_DRAW);

	//// 3rd attribute buffer : normals
	//glEnableVertexAttribArray(normalLoc);
	//glBindBuffer(GL_ARRAY_BUFFER, normalbuffer[0]);
	//glVertexAttribPointer(normalLoc, 3,	GL_FLOAT, GL_FALSE,	0, (void*)0);

	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, normalbuffer[1]);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, normalIndices.size()*sizeof(normalIndices[0]), &normalIndices[0], GL_STATIC_DRAW);
	//ExitOnGLError("ERROR: Could not bind the IBO to the VAO");

	//printf("Model loaded with %d vertices and %d faces\n", vertices.size(), vertexIndices.size()/3);
	//indexCount = vertexIndices.size();
	return myVOAID;
}