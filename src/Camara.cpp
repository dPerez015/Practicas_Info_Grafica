#include "Camara.h"


Camara::Camara(int f, glm::vec3 pos,glm::vec3 target) {
	fov = f;
	cameraPos = pos;
	cameraSpeed =5.0f;
	cameraTarget = target;

	
	//viewMatrix manual
	CalculateLookAt();
	
	viewMatAuto = glm::lookAt(cameraPos, cameraPos+cameraFront,cameraUp);
}

glm::mat4 Camara::LookAt() { return viewMat; }

void Camara::CalculateLookAt() {
	cameraFront = cameraPos - cameraTarget;
	cameraFront = glm::normalize(cameraFront);

	cameraRight = glm::cross(glm::vec3(0, 1, 0), cameraFront);


	cameraUp = glm::cross(cameraFront, cameraRight);

	vecMat[0] = glm::vec4(cameraRight.x, cameraUp.x, cameraFront.x, 0);
	vecMat[1] = glm::vec4(cameraRight.y, cameraUp.y, cameraFront.y, 0);
	vecMat[2] = glm::vec4(cameraRight.z, cameraUp.z, cameraFront.z, 0);
	vecMat[3] = glm::vec4(0, 0, 0, 1);

	transMat[0] = glm::vec4(1, 0, 0, 0);
	transMat[1] = glm::vec4(0, 1, 0, 0);
	transMat[2] = glm::vec4(0, 0, 1, 0);
	transMat[3] = glm::vec4(-cameraPos.x, -cameraPos.y, -cameraPos.z, 1);
	
	viewMat = vecMat*transMat;
}

void Camara::DoMovement(int key) {
	if (key == GLFW_KEY_W) {
		cameraPos = cameraPos + (-cameraFront*cameraSpeed*deltaTime);
		CalculateLookAt();
	}
	else if (key == GLFW_KEY_A) {
		cameraPos = cameraPos - (cameraRight*cameraSpeed*deltaTime);
		CalculateLookAt();
	}
	else if (key == GLFW_KEY_D) {
		cameraPos = cameraPos + (cameraRight*cameraSpeed*deltaTime);
		CalculateLookAt();
	}
	else if (key == GLFW_KEY_S) {
		cameraPos = cameraPos - (-cameraFront*cameraSpeed*deltaTime);
		CalculateLookAt();
	}
}


Camara::~Camara()
{
}


