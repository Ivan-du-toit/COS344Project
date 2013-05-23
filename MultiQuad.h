#ifndef MULTIQUAD_H
#define MULTIQUAD_H

#include "Mesh.h"
#include "Utils.h"

class MultiQuad: public Mesh {
	public:
		MultiQuad(ShaderManager* shader, unsigned int resolution) : Mesh(shader) {
			int width = 0;
			int height = 0;
			
			std::vector<unsigned char> image; //the raw pixels
			unsigned _width, _height;

			//decode
			unsigned error = lodepng::decode(image, _width, _height, "textures/heightmap.png");

			glGenVertexArrays(1, &myVOAID);
			int _vertexCount = indexCount = 6*resolution*resolution;
   
			GLfloat* positions = new float[_vertexCount * 3];
			GLfloat* normals = new float[_vertexCount * 3];
			int index = -1;
			const float heightDamp = 0.6f;
			const float heightOffset = -80.0f;

			float** heighs = new float*[resolution+1];

			float mappedHeight = 0.0f;
			for (int r=0; r<resolution+1; r++) {
				heighs[r] = new float[resolution+1];
				for (int c=0; c<resolution+1; c++) {
					mappedHeight = image[(r*_width+c)*4] + image[(r*_width+(c+1))*4] + image[(r*_width+(c+2))*4]
						+ image[((r+1)*_width+c)*4] + image[((r+1)*_width+(c+1))*4] + image[((r+2)*_width+(c+2))*4]
						+ image[((r+2)*_width+c)*4] + image[((r+2)*_width+(c+1))*4] + image[((r+2)*_width+(c+2))*4];
					heighs[r][c] = (mappedHeight/9) * heightDamp + heightOffset;
				}
			}

			for (int r=0; r<resolution; r++) {
				for (int c=0; c<resolution; c++) {
					positions[index + 1] = .0f + r;
					positions[index + 2] = heighs[r][c];
					positions[index + 3] = .0f + c;
					index += 3;

					positions[index + 1] = .0f + r;
					positions[index + 2] = heighs[r][c+1];
					positions[index + 3] = 1.0f + c;
					index += 3;

					positions[index + 1] = 1.0f + r;
					positions[index + 2] = heighs[r+1][c+1];
					positions[index + 3] = 1.0f + c;
					index += 3;

					positions[index + 1] = .0f + r;
					positions[index + 2] = heighs[r][c];
					positions[index + 3] = .0f + c;
					index += 3;

					positions[index + 1] = 1.0f + r;
					positions[index + 2] = heighs[r+1][c+1];
					positions[index + 3] = 1.0f + c;
					index += 3;

					positions[index + 1] = 1.0f + r;
					positions[index + 2] = heighs[r+1][c];
					positions[index + 3] = .0f + c;
					index += 3;
				}
			}

			for (int r=0; r<resolution+1; r++)
				delete heighs[r];
			delete heighs;

			for (int i = 0; i < _vertexCount; i++) {
				int index = i * 3;
				normals[index + 1] = 0.0f;
				normals[index + 2] = 1.0f;
				normals[index + 3] = 0.0f;
			}

			const GLsizei VERTEX_ARRAY_SIZE = _vertexCount * 3 * (GLsizei)sizeof(float);
	
			glBindVertexArray(myVOAID);
			GLuint buffers[2];
			glGenBuffers(2, buffers);
			if (shader->hasAttribute("position")) {
				glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
				glBufferData(GL_ARRAY_BUFFER, VERTEX_ARRAY_SIZE, positions, GL_STATIC_DRAW);

	
				GLuint positionLocation = shader->findAttributeLoc("position");
				glEnableVertexAttribArray(positionLocation);
				glVertexAttribPointer(positionLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
			} else
				printf("[Warning] Position attribute not found.\n");

			if (shader->hasAttribute("normal")) {
				glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
				glBufferData(GL_ARRAY_BUFFER, VERTEX_ARRAY_SIZE, normals, GL_STATIC_DRAW);

				GLuint normalLocation = shader->findAttributeLoc("normal");
				glEnableVertexAttribArray(normalLocation);
				glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
			} else
				printf("[Warning] Normal attribute not found.\n");
			delete[] positions;
		};
	protected:
		GLuint createVOA(){return myVOAID;};
};

#endif

