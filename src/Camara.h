#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Camara {
public:
	Camara(int, glm::vec3, float);
	~Camara();
	glm::mat4 viewMat;
	glm::mat4 projMat;
	glm::vec3 position;
	int fov;
};

