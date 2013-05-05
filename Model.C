#include "model.h"

Model::Model(ShaderManager* shader, Mesh* mesh) {
	_shader = shader;
	_mesh = mesh;
}

Model::~Model() {

}

void Model::bind() {
	glBindVertexArray(_mesh->getVOAID());
	ExitOnGLError("ERROR: Could not bind the VAO for drawing purposes");
}

void Model::transform() {
	glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), _rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, _rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, _rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));

	glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), _translation);
	
	glm::mat4 ModelMatrix = translationMatrix  * rotationMatrix * scaleMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(-0.0f, 0.0f, 0.0f));
	
	glUseProgram(getShaderID());
	ExitOnGLError("ERROR: Could not use the shader program");

	glUniformMatrix4fv(_shader->getUniformLocation("world"), 1, GL_FALSE, glm::value_ptr(ModelMatrix));
	ExitOnGLError("ERROR: Could not set the shader uniforms");
}

void Model::draw() {
	bind();
	transform();
	drawVOA();

	glBindVertexArray(0);
	glUseProgram(0);
}

glm::vec3 Model::getScale() {
	return _scale;
}

void Model::scale(glm::vec3 scale) {
	_scale = _scale + scale;
}

void Model::setAbsoluteScale(glm::vec3 scale) {
	_scale = scale;
}

glm::vec3 Model::getRotation() {
	return _rotation;
}

void Model::rotate(glm::vec3 rotation) {
	_rotation = _rotation + rotation;
}

void Model::setAbsoluteRotation(glm::vec3 rotation) {
	_rotation = rotation;
}

GLuint Model::getShaderID() {
	return _shader->getShaderID();
}

ShaderManager* Model::getShader() {
	return _shader;
}

void Model::setShader(ShaderManager* shader) {
	_shader = shader;
}