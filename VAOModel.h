#ifndef VAOModel_H
#define VAOModel_H

#include <GL/glew.h>

#include "model.h"

class VAOModel : public Model {
	public:
		VAOModel(ShaderManager* shader, Mesh* mesh);
	virtual ~VAOModel();
  protected: 
	virtual void drawVOA();
  private:
};

#endif