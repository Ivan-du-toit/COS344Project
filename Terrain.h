#ifndef TERRAIN_H
#define TERRAIN_H

#include "VAOModel.h"
#include "Shader.h"

#include "lodepng.h"

class Terrain : public VAOModel {
	public:
		Terrain(ShaderManager* shader, Mesh* mesh) : VAOModel(shader, mesh) {
			glUseProgram(shader->getShaderID());
			glActiveTexture(GL_TEXTURE1);

			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_2D, textureID);
	
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
			int width = 0;
			int height = 0;
			
			std::vector<unsigned char> image; //the raw pixels
			unsigned _width, _height;

			//decode
			unsigned error = lodepng::decode(image, _width, _height, "textures/LavaCracks.png");
			//unsigned char* data = loadTexturePNG("heightmap.png", width, height);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
			ExitOnGLError("Terrain texture not loaded!!!");
			glBindTexture(GL_TEXTURE_2D, 0);
		};

		virtual void bind() {
			glUseProgram(_shader->getShaderID());
			VAOModel::bind();
			glBindTexture(GL_TEXTURE_2D, textureID);
			ExitOnGLError("Could not bind terrain texture");
		};

	protected:
		GLuint textureID;
};

#endif