#ifndef REFLECTIVE_SPHERE_H
#define REFLECTIVE_SPHERE_H

#include "Sphere.h"
#include "lodepng.h"

class ReflectiveSphere : public Sphere {
	public:
		ReflectiveSphere(ShaderManager* shader, Mesh* mesh) : Sphere(shader, mesh) {
			glActiveTexture(GL_TEXTURE0);
			glGenTextures(1, &textureID);
			glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);

			std::vector<unsigned char> image; //the raw pixels
			unsigned width, height;

			lodepng::decode(image, width, height, "textures/terrain_positive_x.png");
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
			image.clear();

			lodepng::decode(image, width, height, "textures/terrain_negative_x.png");
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
			image.clear();

			lodepng::decode(image, width, height, "textures/terrain_positive_y.png");
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
			image.clear();

			lodepng::decode(image, width, height, "textures/terrain_negative_y.png");
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
			image.clear();

			lodepng::decode(image, width, height, "textures/terrain_positive_z.png");
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
			image.clear();

			lodepng::decode(image, width, height, "textures/terrain_negative_z.png");
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);
			image.clear();
		};
	protected:
		virtual void bind() {
			Sphere::bind();
			glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
		};

		GLuint textureID;
};

#endif