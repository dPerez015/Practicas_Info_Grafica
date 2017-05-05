//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include "Shader.h"
#include "Camara.h"
#include "Model.h"

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
glm::mat4 transformMat;
glm::mat4 transformMatCubes;
//glm::mat4 translationMat;
//glm::mat4 rotationMat;
//glm::mat4 scaleMat;

glm::vec3 translateVector;
glm::vec3 scaleVector;
float rotationX;
float rotationY;

float rotateSpeed=90;

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

	//cargamos los shader
	//Shader shader("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");
	Shader shader("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");
	
	//activacion del test de profundidad
	glEnable(GL_DEPTH_TEST);
	
	//activacion del raton
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glfwSetCursorPosCallback(window, MouseMov);
	glfwSetScrollCallback(window, MouseScroll);
#pragma region Buffers

#pragma endregion
#pragma region Texturas	
	//texturas

#pragma endregion

#pragma region Matrices
	scaleVector=glm::vec3(0.2,0.2,0.2);
	translateVector = glm::vec3(0,0,0);
	rotationX = glm::radians(0.f);
	transformMat = glm::scale(transformMat, scaleVector);
	
	//pasamos la velocidad de rotacion a radianes
	rotateSpeed *= glm::pi<float>()/180;

#pragma endregion


#pragma region Modelos
	Model nanosuit("E:/enti/segundo/informatica grafica/practica1/Practicas_Info_Grafica/src/nanosuit/nanosuit.obj");
	Model casa("E:/enti/segundo/informatica grafica/practica1/Practicas_Info_Grafica/src/casa/casa.obj");
	Model ara�a("E:/enti/segundo/informatica grafica/practica1/Practicas_Info_Grafica/src/spider/spider.obj");
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
		//Establecer el color de fondo
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glClearColor(backgroundColor.R, backgroundColor.G, backgroundColor.B, 1.0);

		//establecer el shader
		shader.USE();

		//camara
		camara.CalculateLookAt();

		projMat = glm::perspective(glm::radians((float)camara.FOV), ((float)screenWithd) / ((float)screenHeight), 0.1f, 200.f);

		glUniformMatrix4fv(glGetUniformLocation(shader.Program,"transformMat"), 1, GL_FALSE, glm::value_ptr(transformMat));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "viewMat"), 1, GL_FALSE, glm::value_ptr(camara.viewMat));
		glUniformMatrix4fv(glGetUniformLocation(shader.Program, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));

		

		//pintar
		//nanosuit.Draw(shader, GL_FRONT_AND_BACK);
		//ara�a.Draw(shader, GL_FRONT_AND_BACK);
		casa.Draw(shader, GL_FRONT_AND_BACK);
		glBindVertexArray(0);
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}



	// Terminate GLFW, clearing any resources allocated by GLFW.
	exit(EXIT_SUCCESS);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	
	//salir
	if (key == GLFW_KEY_ESCAPE&&action == GLFW_PRESS) {
		stillGoingOn = false;
	}
}

