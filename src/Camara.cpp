
#include "Camara.h"
#include <GL\glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

Camara::Camara(int f, glm::vec3 pos,glm::vec3 dir) {
	fov = f;
	position = pos;

	
	vecDirection = position-dir;
	vecDirection = glm::normalize(vecDirection);

	vecRight = glm::cross(glm::vec3(0,1,0), vecDirection);
	//vecRight = glm::normalize(vecRight);

	vecUp = glm::cross( vecDirection, vecRight);

	//viewMatrix manual
	glm::mat4 vecMat;
	vecMat[0] = glm::vec4(vecRight.x, vecRight.y, vecRight.z,0);
	vecMat[1] = glm::vec4(vecUp.x, vecUp.y, vecUp.z, 0);
	vecMat[2] = glm::vec4(vecDirection.x, vecDirection.y, vecDirection.z, 0);
	vecMat[3] = glm::vec4(0,0,0,1);
	
	glm::mat4 transMat;
	transMat[0] = glm::vec4(1, 0, 0, -position.x);
	transMat[1] = glm::vec4(0, 1, 0, -position.y);
	transMat[2] = glm::vec4(0, 0, 1, -position.z);
	transMat[3] =glm::vec4(0,0,0,1);

	viewMat = glm::transpose(vecMat)*glm::transpose(transMat);
	viewMatAuto = glm::lookAt(position, position+vecDirection,vecUp);
}


Camara::~Camara()
{
}


