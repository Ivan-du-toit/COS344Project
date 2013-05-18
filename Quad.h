#ifndef QUAD_H
#define QUAD_H

#include "Mesh.h"
#include "Utils.h"

class Quad: public Mesh {
	public:
		Quad(ShaderManager* shader);
	protected:
		GLuint createVOA(){return myVOAID;};
};

#endif

