#include "ObjLoader.h"

ObjLoader::ObjLoader(ShaderManager* shader):Mesh(shader) {
	glGenVertexArrays(1, &myVOAID);
	int _vertexCount = 36;
   
	//GLfloat* positions = new float[_vertexCount * 3];
	GLfloat* normals = new float[_vertexCount * 3];
    int index = -1;

    /*positions[index + 1] = -.5f;
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
    positions[index + 3] = -.5f;*/

	for (int i = 0; i < _vertexCount; i++) {
		int index = i * 3;
		normals[index + 1] = 0.0f;
		normals[index + 2] = 1.0f;
		normals[index + 3] = 0.0f;
	}

	

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> vnormals; // Won't be used at the moment.
	bool res = loadOBJ("meshes/monkey.obj", vertices, uvs, vnormals);
	const GLsizei VERTEX_ARRAY_SIZE = vertices.size() * 3 * (GLsizei)sizeof(float);
	indexCount = vertices.size() * 3;
	GLfloat* positions = new float[vertices.size() * 3];
	for (int i = 0; i < vertices.size(); i++) {
		int index = i * 3;
		positions[index] = vertices[i].x;
		positions[index + 1] = vertices[i].y;
		positions[index + 2] = vertices[i].z;
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
	/*GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	_shader = shader;
	// Create and compile our GLSL program from the shaders
	GLuint programID = _shader->getShaderID();//LoadShaders( "TransformVertexShader.vertexshader", "TextureFragmentShader.fragmentshader" );

	// Load the texture
	//GLuint Texture = loadDDS("uvmap.DDS");
	
	// Get a handle for our "myTextureSampler" uniform
	//TextureID = glGetUniformLocation(programID, "myTextureSampler");

	// Read our .obj file
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals; // Won't be used at the moment.
	bool res = loadOBJ("cube.obj", vertices, uvs, normals);

	// Load it into a VBO

	vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	indexCount = vertices.size();

	//GLuint uvbuffer;
	//glGenBuffers(1, &uvbuffer);
	//glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	//glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);*/
}
/*
void ObjLoader::draw() {
	// Use our shader
	glUseProgram(_shader->getShaderID());

	// Compute the MVP matrix from keyboard and mouse input
	//computeMatricesFromInputs();
	//glm::mat4 ProjectionMatrix = glm::perspective(45.0f, (float)800 / (float)600, 0.1f, 100.0f);//getProjectionMatrix();
	//glm::mat4 ViewMatrix = glm::lookAt(glm::vec3(0,2,0), glm::vec3(0,0,0), glm::vec3(0,1,0));//getViewMatrix();
	//glm::mat4 ModelMatrix = glm::mat4(1.0);
	//glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

	// Get a handle for our "MVP" uniform
	//GLuint MatrixID = glGetUniformLocation(shader->getShaderID(), "MVP");

	// Send our transformation to the currently bound shader, 
	// in the "MVP" uniform
	//glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

	// Bind our texture in Texture Unit 0
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, Texture);
	// Set our "myTextureSampler" sampler to user Texture Unit 0
	//glUniform1i(TextureID, 0);

	// 1rst attribute buffer : vertices
	//glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	//glVertexAttribPointer(0, 3,	GL_FLOAT, GL_FALSE, 0, (void*)0);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
}*/

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
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		
		if ( strcmp( lineHeader, "v" ) == 0 ){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}else if ( strcmp( lineHeader, "vt" ) == 0 ){
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y );
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
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
				printf("File can't be read by our simple parser :-( Try exporting with other options\n");
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