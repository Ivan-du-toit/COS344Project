#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <vector>

#include "Utils.h"

class ShaderManager {
	public:	
		ShaderManager();
		virtual ~ShaderManager();
		ShaderManager* addShader(const char* name, GLenum shader_type);
		ShaderManager* linkShaders();
		
		virtual GLuint getUniformLocation(const char* name);
		virtual GLuint getShaderID();
		virtual bool hasUniform(const char* name);
		GLuint findAttributeLoc(const char* name);
		bool hasAttribute(const char* name);
	protected:
		GLuint programID;
		std::vector<GLuint> shaders;
};

#endif