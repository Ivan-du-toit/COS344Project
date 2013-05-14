#include "Shader.h"

ShaderManager::ShaderManager() {
	programID = glCreateProgram();
	ExitOnGLError("ERROR: Could not create the shader program");
}

ShaderManager::~ShaderManager() {
	for (unsigned i=0; i<shaders.size(); i++) {
		glDetachShader(programID, shaders[i]);
		glDeleteShader(shaders[i]);
		ExitOnGLError("ERROR: Could not destroy the shaders");
	}
	glDeleteProgram(programID);
}

ShaderManager* ShaderManager::addShader(const char* filename, GLenum shader_type) {
	GLuint shader_id = 0;
	FILE* file;
	long file_size = -1;
	char* glsl_source;

	if (NULL != (file = fopen(filename, "rb")) &&
		0 == fseek(file, 0, SEEK_END) &&
		-1 != (file_size = ftell(file))) {
		rewind(file);
		if (NULL != (glsl_source = (char*)malloc(file_size + 1))) {
			if (file_size == (long)fread(glsl_source, sizeof(char), file_size, file)) {
				glsl_source[file_size] = '\0';

				if (0 != (shader_id = glCreateShader(shader_type))) {
					glShaderSource(shader_id, 1, (const GLchar**)&glsl_source, NULL);
					glCompileShader(shader_id);
					ExitOnGLError("Could not compile a shader");
				} else
					fprintf(stderr, "ERROR: Could not create a shader.\n");
			} else
				fprintf(stderr, "ERROR: Could not read file %s\n", filename);
			free(glsl_source);
		} else
			fprintf(stderr, "ERROR: Could not allocate %i bytes.\n", (int)file_size);
		fclose(file);
	} else
		fprintf(stderr, "ERROR: Could not open file %s\n", filename);

	glAttachShader(programID, shader_id);
	shaders.push_back(shader_id);
	return this;
}

ShaderManager* ShaderManager::linkShaders() {
	glLinkProgram(programID);
	ExitOnGLError("ERROR: Could not link the shader program");
	return this;
}

GLuint ShaderManager::getUniformLocation(const char* name) {
	return glGetUniformLocation(programID, name);
}

GLuint ShaderManager::getAtrributeLocation(const char* name) {
	return glGetAttribLocation(programID, name);
}

GLuint ShaderManager::getShaderID() {
	return programID;
}

bool ShaderManager::hasUniform(const char* name) {
	return (getUniformLocation(name) != -1);
}