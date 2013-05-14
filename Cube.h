#ifndef CUBE_H
#define CUBE_H

#include "Mesh.h"

#include <GL/glew.h>
#include <GL/freeglut.h>

class Cube: public Mesh {
	public:
		Cube(ShaderManager* shader) : Mesh(shader) {
			myVOAID = createVOA();
		}
		~Cube() {
			glDeleteBuffers(2, &BufferIds[0]);
			glDeleteVertexArrays(1, &myVOAID);
			ExitOnGLError("ERROR: Could not destroy the buffer objects");
		};
	protected:
		GLuint createVOA() {
			const GLfloat VERTICES[] = {
				-1.0f, -1.0f, 1.0f,
				-1.0f, 1.0f, 1.0f,
				1.0f, 1.0f, 1.0f,
				1.0f, -1.0f, 1.0f,
				-1.0f, -1.0f, -1.0f,
				-1.0f, 1.0f, -1.0f,
				1.0f, 1.0f, -1.0f,
				1.0f, -1.0f, -1.0f,
			};

			const GLuint INDICES[36] = {
				0,2,1,  0,3,2,
				4,3,0,  4,7,3,
				4,1,5,  4,0,1,
				3,6,2,  3,7,6,
				1,6,5,  1,2,6,
				7,5,6,  7,4,5
			};
		
			glGenVertexArrays(1, &myVOAID);
	
			ExitOnGLError("ERROR: Could not generate the VAO");
	
			glBindVertexArray(myVOAID);
			ExitOnGLError("ERROR: Could not bind the VAO");

			GLint positionLoc = getAttributeLocation("position");
			GLint colourLoc = getAttributeLocation("colour");
			GLint normalLoc = getAttributeLocation("normal");

			//printf("normal: %d\n", normalLoc);
			glEnableVertexAttribArray(positionLoc);
			//glEnableVertexAttribArray(normalLoc);
			ExitOnGLError("ERROR: Could not enable vertex attributes");

			glGenBuffers(2, &BufferIds[0]);
			ExitOnGLError("ERROR: Could not generate the buffer objects");

			glBindBuffer(GL_ARRAY_BUFFER, BufferIds[0]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);
			ExitOnGLError("ERROR: Could not bind the VBO to the VAO");

			glVertexAttribPointer(positionLoc, 3, GL_FLOAT, GL_FALSE, 3*sizeof(VERTICES[0]), (GLvoid*)0);
			if (colourLoc > -1) {
				glEnableVertexAttribArray(colourLoc);
				glVertexAttribPointer(colourLoc, 3, GL_FLOAT, GL_FALSE, 3*sizeof(VERTICES[0]), (GLvoid*)0);
			}

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferIds[1]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES), INDICES, GL_STATIC_DRAW);
			ExitOnGLError("ERROR: Could not bind the IBO to the VAO");
			
			/*glBindBuffer(GL_ARRAY_BUFFER, BufferIds[2]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);
			ExitOnGLError("ERROR: Could not bind the VBO to the VAO");

			glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, 3*sizeof(VERTICES[0]), (GLvoid*)0);
			ExitOnGLError("ERROR: Could not set VAO attributes");*/


			indexCount = sizeof(INDICES);
			return myVOAID;
		};
	private:
		GLuint BufferIds[2];
};

#endif