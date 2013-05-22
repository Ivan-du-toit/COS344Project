#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Shader.h"
#include "Mesh.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wconversion"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#pragma GCC diagnostic pop

bool loadOBJ(
	const char * path, 
	std::vector<glm::vec3> & out_vertices, 
	std::vector<glm::vec2> & out_uvs, 
	std::vector<glm::vec3> & out_normals
);

class ObjLoader: public Mesh {
	public:
		ObjLoader(ShaderManager* shader, const char* file);
		//void draw();
		ShaderManager* _shader;
	protected:
		GLuint createVOA(){return vertexbuffer;};
	private:
		GLuint vertexbuffer;
		//GLuint vertexCount;
};

#endif