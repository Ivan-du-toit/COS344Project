#ifndef LOADED_MESH_H
#define LOADED_MESH_H

#include "Mesh.h"
#include "Utils.h"

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wconversion"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#pragma GCC diagnostic pop

class LoadedMesh: public Mesh {
public:
		LoadedMesh(const char* filename, ShaderManager* shader);
		~LoadedMesh();
	protected:
		GLuint createVOA();
	private:
		const char* _filename;
		GLuint BufferIds[4];
};
#endif