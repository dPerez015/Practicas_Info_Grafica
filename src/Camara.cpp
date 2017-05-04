#include "Camara.h"


Camara::Camara(int f, glm::vec3 pos,glm::vec3 target) {
	FOV = f;
	cameraPos = pos;
	cameraSpeed =5.0f;

	cameraFront = target- cameraPos;
	cameraFront = glm::normalize(cameraFront);

	//viewMatrix manual
	CalculateLookAt();
	
	Sensitivity = 0.3;
	
	firstMouse = true;

	PITCH = 0;
	YAW = glm::radians(-90.f);

}

glm::mat4 Camara::LookAt() { return viewMat; }

void Camara::CalculateLookAt() {
	cameraRight = glm::cross( cameraFront,glm::vec3(0, 1, 0) );
	cameraRight = glm::normalize(cameraRight);
	cameraUp = glm::cross( cameraRight, cameraFront);
	//cameraRight = glm::cross(cameraUp, camera);
	vecMat[0] = glm::vec4(cameraRight.x, cameraUp.x, -cameraFront.x, 0);
	vecMat[1] = glm::vec4(cameraRight.y, cameraUp.y, -cameraFront.y, 0);
	vecMat[2] = glm::vec4(cameraRight.z, cameraUp.z, -cameraFront.z, 0);
	vecMat[3] = glm::vec4(0				,0			,0				,1);

	transMat[0] = glm::vec4(1				, 0			, 0			, 0);
	transMat[1] = glm::vec4(0				, 1			, 0			, 0);
	transMat[2] = glm::vec4(0				, 0			, 1			, 0);
	transMat[3] = glm::vec4(-cameraPos.x, -cameraPos.y, -cameraPos.z, 1);
	
	viewMat = vecMat*transMat;
	//autoviewMat = glm::lookAt(cameraPos,cameraPos+cameraFront ,cameraUp);
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
		nextMove += (cameraFront);
	}
	if (states[1]) {
		nextMove -= cameraRight;
	}
	if (states[2] ) {
		nextMove += cameraRight;
	}
	if (states[3] ) {
		nextMove -= (cameraFront);
	}

	cameraPos += nextMove*cameraSpeed*deltaTime;
	
}

void Camara::MouseMove(GLFWwindow* window, double xpos, double ypos) {
	if (firstMouse) {
		LastMx = xpos;
		LastMy = ypos;
		firstMouse = false;
	}
	YAW = glm::mod(YAW + glm::radians((xpos - LastMx)*Sensitivity), glm::two_pi<double>());
	PITCH = glm::clamp(PITCH + glm::radians((LastMy-ypos )*Sensitivity), glm::radians<double>(-89.f) , glm::radians<double>(89.f));

	LastMx = xpos;
	LastMy = ypos;

	//rotacion
	cameraFront.x = glm::cos(PITCH)*glm::cos(YAW);
	cameraFront.y = glm::sin(PITCH);
	cameraFront.z = glm::cos(PITCH)*sin(YAW);

	cameraFront = glm::normalize(cameraFront);

}

void Camara::MouseScroll(GLFWwindow* window, double xScroll, double yScroll) {
	FOV -= yScroll;
	if (FOV < 1.0f) FOV = 1;
	else if (FOV>120) FOV = 120.0f;
}

GLfloat Camara::GetFOV() { return FOV; }

Camara::~Camara()
{
}


