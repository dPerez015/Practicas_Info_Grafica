#pragma once
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

class Camara {
public:
	Camara(int, glm::vec3,glm::vec3);
	~Camara();
	void DoMovement(GLFWwindow*);
	void MouseMove(GLFWwindow* window, double xpos, double ypos);
	void MouseScroll(GLFWwindow* window, double xScroll, double yScroll);
	glm::mat4 LookAt();
	void CalculateLookAt();
	GLfloat GetFOV();

	//posicion
	glm::vec3 cameraPos;
	float cameraSpeed;
	glm::vec3 nextMove;

	//vectores directores
	glm::vec3 cameraTarget;
	glm::vec3 cameraFront;
	glm::vec3 cameraRight;
	glm::vec3 cameraUp;
	
	//delta time
	float lastFrameTime;
	float currentTime;
	float deltaTime;

	//matrices
	glm::mat4 viewMat;
	glm::mat4 viewMatAuto;
	glm::mat4 vecMat;
	glm::mat4 transMat;
	int fov;

	//key states
	bool states[4];
};

