#ifndef QUAD_H
#define QUAD_H

#include <cmath>
#include <cstdlib>

#include <GL/glew.h>

#include "Mesh.h"

class Quad: public Mesh
{
   public:
      Quad(ShaderManager* shader);
	protected:
		GLuint createVOA(){return myVOAID;};
};

#endif

