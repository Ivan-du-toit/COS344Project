#ifndef POSITIONABLE_H
#define POSITIONABLE_H

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Wconversion"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#pragma GCC diagnostic pop

class Positionable {
	public:
		Positionable() {
			_translation = glm::vec3(0.0f);
		}
		
		glm::vec3 getTranslation();
		void translate(glm::vec3);
		void setAbsolutePosition(glm::vec3);
	protected:
		glm::vec3 _translation;
};

#endif