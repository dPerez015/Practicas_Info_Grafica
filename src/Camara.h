#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Camara {
public:
	Camara(int, glm::vec3,glm::vec3);
	~Camara();
	glm::mat4 viewMat;
	glm::mat4 viewMatAuto;
	glm::vec3 position;
	glm::vec3 vecDirection;
	glm::vec3 vecRight;
	glm::vec3 vecUp;
	int fov;
};

