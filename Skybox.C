#include "Skybox.h"

Skybox::Skybox() {
	glEnable(GL_TEXTURE_CUBE_MAP);
	ExitOnGLError("start");
	glActiveTexture(GL_TEXTURE1);
	ExitOnGLError("NOOO");
    
	ExitOnGLError("No");
    glGenTextures(1, &texture);
	ExitOnGLError("No");
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	ExitOnGLError("WTF!!!");
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	/*Texture xpos = Texture("textures/grimmnightLF.bmp");
	Texture xneg = Texture("textures/grimmnightRT.bmp");
	Texture ypos = Texture("textures/grimmnightUP.bmp");
	Texture yneg = Texture("textures/grimmnightDN.bmp");
	Texture zpos = Texture("textures/grimmnightBK.bmp");
	Texture zneg = Texture("textures/grimmnightFT.bmp");*/
	ExitOnGLError("WTFddd");
	CImg<float> image("textures/grimmnightLF.bmp");
	//glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, xpos.getWidth(), xpos.getHeight(), 0, GL_RGB, GL_BITMAP, xpos.getColours());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, image.width(), image.height(), 0, GL_RGB, GL_FLOAT, image.data());
	ExitOnGLError("WTF123");
    /*glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, xneg.getWidth(), xneg.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, xneg.getColours());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, ypos.getWidth(), ypos.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, ypos.getColours());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, yneg.getWidth(), yneg.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, yneg.getColours());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, zpos.getWidth(), zpos.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, zpos.getColours());
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, zneg.getWidth(), zneg.getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, zneg.getColours());*/

	
	ShaderManager shader = ShaderManager();
	shader.addShader("shaders/skybox/vertex.glsl", GL_VERTEX_SHADER);
	shader.addShader("shaders/skybox/fragment.glsl", GL_FRAGMENT_SHADER);
	shader.linkShaders();
	ExitOnGLError("WTF2");
	GLint PVM    = glGetUniformLocation(shader.getShaderID(), "PVM");
	GLint vertex = glGetAttribLocation(shader.getShaderID(), "vertex");

	// cube vertices for vertex buffer object
	GLfloat cube_vertices[] = {
	  -1.0,  1.0,  1.0,
	  -1.0, -1.0,  1.0,
	   1.0, -1.0,  1.0,
	   1.0,  1.0,  1.0,
	  -1.0,  1.0, -1.0,
	  -1.0, -1.0, -1.0,
	   1.0, -1.0, -1.0,
	   1.0,  1.0, -1.0,
	};
	GLuint vbo_cube_vertices;
	glGenBuffers(1, &vbo_cube_vertices);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_cube_vertices);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
 
	// cube indices for index buffer object
	GLushort cube_indices[] = {
	  0, 1, 2, 3,
	  3, 2, 6, 7,
	  7, 6, 5, 4,
	  4, 5, 1, 0,
	  0, 3, 7, 4,
	  1, 2, 6, 5,
	};
	GLuint ibo_cube_indices;
	glGenBuffers(1, &ibo_cube_indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_indices), cube_indices, GL_STATIC_DRAW);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	GLuint indexCount = sizeof(cube_indices)/sizeof(GLushort);
	
	glEnableVertexAttribArray(vertex);
	glVertexAttribPointer(vertex, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glm::mat4 Projection = glm::perspective(45.0f, (float)800 / (float)600, 0.1f, 100.0f); 
	glm::mat4 View       = glm::mat4(1.0f);
	glm::mat4 Model      = glm::scale(glm::mat4(1.0f),glm::vec3(50,50,50));

	//glm::mat4 RotateX = glm::rotate(glm::mat4(1.0f), alpha, glm::vec3(-1.0f, 0.0f, 0.0f));
	//glm::mat4 RotateY = glm::rotate(RotateX, beta, glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 M = Projection * View * Model;// * RotateY;
	glUniformMatrix4fv(PVM, 1, GL_FALSE, glm::value_ptr(M));
}

void Skybox::draw() {
	glDrawElements(GL_QUADS, indexCount, GL_UNSIGNED_SHORT, 0);
}
 
Skybox::~Skybox() {
    glDeleteTextures(1, &texture);
}