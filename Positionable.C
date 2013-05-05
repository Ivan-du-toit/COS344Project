#include "Positionable.h"

glm::vec3 Positionable::getTranslation() {
	return _translation;
}

void Positionable::translate(glm::vec3 translation) {
	_translation = _translation + translation;
}

void Positionable::setAbsolutePosition(glm::vec3 position) {
	_translation = position;
}