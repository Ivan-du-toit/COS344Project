#ifndef SPHERE_H
#define SPHERE_H

#include <GL/glew.h>
#include <GL/freeglut.h>

#include "Model.h"
#include "Utils.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wconversion"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#pragma GCC diagnostic pop

class Sphere : public Model{
  public:
    Sphere(ShaderManager* shader, Mesh* mesh);
	virtual ~Sphere();
  protected: 
    //virtual void createVOA();
	virtual void drawVOA();
  private:
};

#endif