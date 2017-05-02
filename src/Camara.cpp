
#include "Camara.h"
#include <GL\glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

Camara::Camara(int f, glm::vec3 pos, float ratio) {
	fov = f;
	position = pos;
	projMat = glm::perspective<float>((float)fov, ratio, 0.f, 20.f);
	viewMat = glm::translate(viewMat, position);
	viewMat = glm::inverse(viewMat);
}


Camara::~Camara()
{
}


