//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include "Shader.h"
#include "Camara.h"
#include "Model.h"
#include "Object.h"
#include "Light.h"

#include <SOIL.h>
//glm
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace std;
const GLint WIDTH = 800, HEIGHT = 600;
bool WIDEFRAME = false;
bool stillGoingOn = true;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

float AngularSpeed = 3.141592;
float actualAngle = 0;
//matriz de proyeccion
glm::mat4 projMat;

//variables para el mix de texturas
float textureChangeSpeed = 1;
float textureMixRate = 0;
//info del cuadrado
struct Color {
	float R, G, B;
};

GLfloat vertices[] = {
	// Positions          // Colors           // Texture Coords
	0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // Top Right
	0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // Bottom Right
	-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // Bottom Left
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // Top Left 
};
GLuint indices[6] = {
	0,1,3,
	1,2,3
};

GLfloat VertexBufferCube[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	0.5f , -0.5f, -0.5f,  1.0f, 0.0f,
	0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f ,  0.5f,  0.5f,  1.0f, 1.0f,
	0.5f ,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f , -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f , -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f , -0.5f,  0.5f,  0.0f, 0.0f,
	0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	0.5f , -0.5f, -0.5f,  1.0f, 1.0f,
	0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
	0.5f , -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	0.5f ,  0.5f, -0.5f,  1.0f, 1.0f,
	0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
	0.5f ,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
glm::vec3 CubesPositionBuffer[] = {
	glm::vec3(0.0f ,  0.0f,  0.0f),
	glm::vec3(2.0f ,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f , -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f , -2.0f, -2.5f),
	glm::vec3(1.5f ,  2.0f, -2.5f),
	glm::vec3(1.5f ,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};


//matrices
glm::mat4 transformMat1;
glm::mat4 transformMat2;
glm::mat4 transformMat3;

//glm::mat4 translationMat;
//glm::mat4 rotationMat;
//glm::mat4 scaleMat;

glm::vec3 translateVector;
glm::vec3 scaleVector;
float rotationX;
float rotationY;
bool renderModel1=false;
bool renderModel2 = true;
bool renderModel3 = false;

Camara camara(60, glm::vec3(0, 0, 3.0), glm::vec3(0, 0, 0));

void flipTexture(GLfloat* arr, int offset,int stride, int count) {
	for (int i = 0; i < count; i++) {
		arr[i*stride + offset] = 1 - arr[i*stride + offset];
	}
}

void MouseMov(GLFWwindow* window, double xpos, double ypos) {
	camara.MouseMove(window, xpos, ypos);
}
void MouseScroll(GLFWwindow* window, double xpos, double ypos) {
	camara.MouseScroll(window, xpos, ypos);
}
int main() {

#pragma region init
	//initGLFW
	GLFWwindow* window;

	if (!glfwInit())
		exit(EXIT_FAILURE);

	//set GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	//create a window
	window = glfwCreateWindow(WIDTH, HEIGHT, "Primera ventana", nullptr, nullptr);
	if (!window) {
		cout << "Error al crear la ventana" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwMakeContextCurrent(window);

	//set GLEW and inicializate
	glewExperimental = GL_TRUE;
	if (GLEW_OK != glewInit()) {
		std::cout << "Error al inicializar glew" << std::endl;
		glfwTerminate();
		return NULL;
	}

	//set function when callback
	glfwSetKeyCallback(window, key_callback);

	//set windows and viewport

	int screenWithd, screenHeight;
	glfwGetFramebufferSize(window, &screenWithd, &screenHeight);
	
	glViewport(0,0,screenWithd, screenHeight);

	//fondo
	Color backgroundColor;
	backgroundColor.R = 0.1;
	backgroundColor.G = 0.1;
	backgroundColor.B = 0.1;

	//activacion del test de profundidad
	glEnable(GL_DEPTH_TEST);
	
	//activacion del raton
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(window, MouseMov);
	glfwSetScrollCallback(window, MouseScroll);
#pragma endregion

#pragma region Matrices
	scaleVector=glm::vec3(1,1,1);
	translateVector = glm::vec3(0,0,0);
	rotationX = glm::radians(0.f);
	transformMat1 = glm::scale(transformMat1, scaleVector);

	scaleVector = glm::vec3(0.05,0.05,0.05);
	transformMat2 = glm::scale(transformMat2,scaleVector);

	scaleVector = glm::vec3(0.005,0.005,0.005);
	//transformMat3 = glm::translate(transformMat3, glm::vec3(0, 0, -10));
	transformMat3 = glm::scale(transformMat3, scaleVector);
	


#pragma endregion

#pragma region luz
	Shader Multiilum("./src/MultiLight.vertexshader","./src/MultiLight.fragmentshader");

	Light directionalLight(vec3(0, 0, 0.f), glm::vec3(0, -1, -1),vec3(100,100,100),lightType::directional);
	Light pointLight1(vec3(2,1.f,0), vec3(0,0,0),vec3(255, 0, 0), lightType::point);
	Light pointLight2(vec3(-2, 1.f, 0), vec3(0, 0, 0), vec3(0, 255, 0), lightType::point);
	Light focalLight1(vec3(0, 1, 0), vec3(0, -1, 0), vec3(0, 0, 255), lightType::focal);
	Light focalLight2(vec3(0, 0, -1), vec3(0, 0, 1), vec3(255, 128, 0), lightType::focal);

#pragma endregion

#pragma region Modelos y objetos

	Object cuboA(glm::vec3 (0.5f,0.5f,0.5f),glm::vec3(0,0,0), glm::vec3 (0,0,0),"./src/Materials/difuso.png", "./src/Materials/especular.png",32.f,Object::FigureType::cube);
	Model nanosuit("./src/nanosuit/nanosuit.obj");

#pragma endregion

	//bucle de dibujado
	camara.lastFrameTime = glfwGetTime();

	while (!glfwWindowShouldClose(window) && stillGoingOn) {
		camara.currentTime = glfwGetTime();
		
		camara.deltaTime = camara.currentTime - camara.lastFrameTime;
		camara.lastFrameTime = camara.currentTime;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		camara.DoMovement(window);
		cuboA.doMovement(window, camara.deltaTime);

		//Establecer el color de fondo
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glClearColor(backgroundColor.R, backgroundColor.G, backgroundColor.B, 1.0);

		//camara
		camara.CalculateLookAt();
		projMat = glm::perspective(glm::radians((float)camara.FOV), ((float)screenWithd) / ((float)screenHeight), 0.1f, 200.f);

		//cargar los parametros de las luces
		Multiilum.USE();
		glUniform1i(glGetUniformLocation(Multiilum.Program, "numPointLights"),2);
		glUniform1i(glGetUniformLocation(Multiilum.Program, "numFocalLights"), 2);
		directionalLight.loadMultipleLightParams(Multiilum, 0);
		pointLight1.loadMultipleLightParams(Multiilum,0);
		pointLight2.loadMultipleLightParams(Multiilum, 1);
		focalLight1.loadMultipleLightParams(Multiilum, 0);
		focalLight2.loadMultipleLightParams(Multiilum, 1);

		glUniform3f(glGetUniformLocation(Multiilum.Program, "viewPos"),camara.cameraPos.x, camara.cameraPos.y, camara.cameraPos.z);
		glUniformMatrix4fv(glGetUniformLocation(Multiilum.Program, "viewMat"), 1, GL_FALSE, glm::value_ptr(camara.viewMat));
		glUniformMatrix4fv(glGetUniformLocation(Multiilum.Program, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
		
		directionalLight.Draw(camara.viewMat, projMat);
		pointLight1.Draw(camara.viewMat, projMat);
		pointLight2.Draw(camara.viewMat, projMat);
		focalLight1.Draw(camara.viewMat, projMat);
		focalLight2.Draw(camara.viewMat, projMat);

		cuboA.Draw(Multiilum);
		
		glUniformMatrix4fv(glGetUniformLocation(Multiilum.Program, "transformMat"), 1, GL_FALSE, glm::value_ptr(transformMat2));
		nanosuit.Draw(Multiilum, GL_FRONT_AND_BACK);
		
		glBindVertexArray(0);
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	// Terminate GLFW, clearing any resources allocated by GLFW.
	exit(EXIT_SUCCESS);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	
	 if (key == GLFW_KEY_ESCAPE&&action == GLFW_PRESS) {
		stillGoingOn = false;
	}
	 else if (key==GLFW_KEY_8) {
		 transformMat2 = translate(transformMat2, vec3(8,0,0)*camara.deltaTime);
	 }
	 else if (key == GLFW_KEY_9) {
		 transformMat2 = translate(transformMat2, vec3(-8, 0, 0)*camara.deltaTime);
	 }
}

