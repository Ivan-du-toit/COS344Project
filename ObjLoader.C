#include "ObjLoader.h"

ObjLoader::ObjLoader(ShaderManager* shader):Mesh(shader) {
	glGenVertexArrays(1, &myVOAID);
	
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> vnormals;
	bool res = loadOBJ("meshes/monkey.obj", vertices, uvs, vnormals);

	const GLsizei VERTEX_ARRAY_SIZE = vertices.size() * 3 * (GLsizei)sizeof(float);
	indexCount = vertices.size() * 3;
	GLfloat* positions = new float[vertices.size() * 3];
	GLfloat* normals = new float[vertices.size() * 3];
	for (int i = 0; i < vertices.size(); i++) {
		int index = i * 3;
		positions[index] = vertices[i].x;
		positions[index + 1] = vertices[i].y;
		positions[index + 2] = vertices[i].z;

		normals[index] = vnormals[i].x;
		normals[index + 1] = vnormals[i].y;
		normals[index + 2] = vnormals[i].z;
	}
	
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

bool loadOBJ(
	const char * path, 
	std::vector<glm::vec3> & out_vertices, 
	std::vector<glm::vec2> & out_uvs,
	std::vector<glm::vec3> & out_normals
){
	printf("Loading OBJ file %s...\n", path);

	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices; 
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;


	FILE * file = fopen(path, "r");
	if( file == NULL ){
		printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
		return false;
	}

	while( 1 ){
		char lineHeader[128];
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;
		
		if ( strcmp( lineHeader, "v" ) == 0 ){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}else if ( strcmp( lineHeader, "vt" ) == 0 ){
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			temp_uvs.push_back(uv);
		}else if ( strcmp( lineHeader, "vn" ) == 0 ){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			temp_normals.push_back(normal);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			//int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
			if (matches != 6){
				printf("File can't be read by parser\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			//uvIndices    .push_back(uvIndex[0]);
			//uvIndices    .push_back(uvIndex[1]);
			//uvIndices    .push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}

	}

	// For each vertex of each triangle
	for( unsigned int i=0; i<vertexIndices.size(); i++ ){

		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		//unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];
		
		// Get the attributes thanks to the index
		glm::vec3 vertex = temp_vertices[ vertexIndex-1 ];
		//glm::vec2 uv = temp_uvs[ uvIndex-1 ];
		glm::vec3 normal = temp_normals[ normalIndex-1 ];
		
		// Put the attributes in buffers
		out_vertices.push_back(vertex);
		//out_uvs     .push_back(uv);
		out_normals .push_back(normal);
	
	}

	return true;
}