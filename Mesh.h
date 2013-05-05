#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdio.h>

#include "Shader.h"

class Mesh {
	public:
		Mesh(ShaderManager* shader);
		virtual ~Mesh();
		GLuint getIndexCount();
		GLuint getVOAID();
	protected:
		virtual GLuint createVOA()=0;
		GLuint myVOAID;
		int indexCount;
		GLuint getAttributeLocation(const char* name);
		ShaderManager* _shader;
};

#endif