#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wconversion"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#pragma GCC diagnostic pop

#include "Positionable.h"
#include "Shader.h"
#include "Mesh.h"

class Model : public Positionable {
	public:
		Model(ShaderManager* shader, Mesh* mesh);
		virtual ~Model();
		void draw();

		glm::vec3 getScale();
		void scale(glm::vec3);
		void setAbsoluteScale(glm::vec3);

		glm::vec3 getRotation();
		void rotate(glm::vec3);
		void setAbsoluteRotation(glm::vec3);

		GLuint getShaderID();
		ShaderManager* getShader();
		void setShader(ShaderManager* shader);
	protected:
		virtual void bind();
		virtual void transform();
		virtual void drawVOA() = 0;
		//virtual void createVOA() = 0;
		
		ShaderManager* _shader;
		Mesh* _mesh;

		glm::vec3 _scale;
		glm::vec3 _rotation;
};
#endif