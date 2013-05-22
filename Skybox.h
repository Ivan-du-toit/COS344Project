#ifndef SKYBOX_H
#define SKYBOX_H

#include "VAOModel.h"
#include "lodepng.h"

class Skybox : public VAOModel {
	public:
		Skybox(ShaderManager* shader, Mesh* mesh) : VAOModel(shader, mesh) {
			glActiveTexture(GL_TEXTURE0);
			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);

			std::vector<unsigned char> image; //the raw pixels
			unsigned width, height;

			//decode
			unsigned error = lodepng::decode(image, width, height, "textures/terrain_positive_x.png");
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
			image.clear();

			//data = loadTexturePNG("terrain_negative_x.png", width, height);
			lodepng::decode(image, width, height, "textures/terrain_negative_x.png");
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
			image.clear();

			//data = loadTexturePNG("terrain_positive_y.png", width, height);
			lodepng::decode(image, width, height, "textures/terrain_positive_y.png");
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
			image.clear();
			//delete[] data;
			//data = loadTexturePNG("terrain_negative_y.png", width, height);
			lodepng::decode(image, width, height, "textures/terrain_negative_y.png");
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
			image.clear();
			//delete[] data;
			//data = loadTexturePNG("terrain_positive_z.png", width, height);
			lodepng::decode(image, width, height, "textures/terrain_positive_z.png");
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
			image.clear();
			//delete[] data;
			//data = loadTexturePNG("terrain_negative_z.png", width, height);
			lodepng::decode(image, width, height, "textures/terrain_negative_z.png");
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
			image.clear();
			//delete[] data;
		};

		virtual void drawVOA() {
			//Disable depth buffering to draw the skybox behind everything.
			glCullFace(GL_FRONT);
			glDepthMask(0); 
			VAOModel::drawVOA();
			glDepthMask(1); 
			glCullFace(GL_BACK);
		};

		virtual void bind() {
			VAOModel::bind();
			glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
		};

	protected:
		GLuint textureID;
};

#endif