#include "Camara.h"


Camara::Camara(int f, glm::vec3 pos,glm::vec3 target) {
	FOV = f;
	cameraPos = pos;
	cameraSpeed =5.0f;

	cameraFront = cameraPos - target;
	cameraFront = glm::normalize(cameraFront);

	//viewMatrix manual
	CalculateLookAt();
	
	Sensitivity = 0.5;
	
	PITCH = glm::asin(cameraFront.y);
	YAW = glm::acos(cameraFront.x)/glm::sin(PITCH);

}

glm::mat4 Camara::LookAt() { return viewMat; }

void Camara::CalculateLookAt() {
	
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

void Camara::DoMovement(GLFWwindow* window) {
	//translacion
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)states[0] = true;
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)states[0] = false;
	
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)states[1] = true;
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)states[1] = false;
	
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)states[2] = true;
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)states[2] = false;
	
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)states[3] = true;
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)states[3] = false;

	nextMove = glm::vec3(0);
	if (states[0]) {
		nextMove += (-cameraFront);
	}
	if (states[1]) {
		nextMove -= cameraRight;
	}
	if (states[2] ) {
		nextMove += cameraRight;
	}
	if (states[3] ) {
		nextMove -= (-cameraFront);
	}

	cameraPos += nextMove*cameraSpeed*deltaTime;
	
	//rotacion
	cameraFront.x = glm::cos(YAW*glm::sin(PITCH));
	cameraFront.y = glm::sin(PITCH);
	cameraFront.z = glm::sin(YAW*sin(PITCH));

}

void Camara::MouseMove(GLFWwindow* window, double xpos, double ypos) {

}

void Camara::MouseScroll(GLFWwindow* window, double xScroll, double yScroll) {

}

GLfloat Camara::GetFOV() { return FOV; }

Camara::~Camara()
{
}


