//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include "Shader.h"


using namespace std;
const GLint WIDTH = 800, HEIGHT = 600;
bool WIDEFRAME = false;
bool useLines = false;
bool stillGoingOn = true;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

float lastFrameTime;
float deltaTime;

struct Color {
	float R, G, B;
};


GLfloat positions[12] = { 
-0.5f,0.f,0.f,
0.5f,0.f,0.f,
0.5f,1.f,0.f,
-0.5f,1.f,0.f 
};

GLuint indices[6] = {
	0,1,3,
	1,2,3
};
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
	//fondo
	Color backgroundColor;
	backgroundColor.R = 1;
	backgroundColor.G = 1;
	backgroundColor.B = 0;
	//color triangulo
	
	//cargamos los shader
	//Shader shader("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");
	Shader shader("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");
	// Definir el buffer de vertices
	GLuint vbo, vao;
	// Definir el EBO
	GLuint ebo;
	// Crear los VBO, VAO y EBO

	//reservar memoria para el VAO, VBO y EBO
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glGenVertexArrays(1, &vao);

	/*
	glBindBuffer(GL_ARRAY_BUFFER | GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBindVertexArray(vao);*/

	glBindVertexArray(vao);
	//Establecer el objeto (VAO)
	//Declarar el VBO y el EBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//Establecer las propiedades de los vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	//
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	//

	glEnableVertexAttribArray(0);

	//cout << "vertices introducidos" <<endl;

	//liberar el buffer
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//liberar el buffer de vertices
	glBindVertexArray(0);

	//Variables uniform
	GLuint uniformSinus = glGetUniformLocation(shader.Program, "Sinus");
	if (uniformSinus == -1) {
		std::cout << "Uniform not found" << std::endl;
	}


	//bucle de dibujado
	while (!glfwWindowShouldClose(window) && stillGoingOn) {
		deltaTime = glfwGetTime() - lastFrameTime;

		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
		//GLFW_KEY_X
		//Establecer el color de fondo
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(backgroundColor.R, backgroundColor.G, backgroundColor.B, 1.0);


		//establecer el shader
		shader.USE();
		
		glUniform1f(uniformSinus,sin());

		//pitar el VAO
		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);

		if (useLines){
			//pintar con lineas
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		else {
			//pintar con triangulos
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// liberar la memoria de los VAO, EBO y VBO
	glDeleteVertexArrays(1,&vao);
	glDeleteBuffers(1,&vbo);
	glDeleteBuffers(1,&ebo);

	lastFrameTime = glfwGetTime();
	// Terminate GLFW, clearing any resources allocated by GLFW.
	exit(EXIT_SUCCESS);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//TODO, comprobar que la tecla pulsada es escape para cerrar la aplicación y la tecla w para cambiar a modo widwframe
	if (key==GLFW_KEY_W&&action==GLFW_PRESS) {
		useLines = !useLines;
	}
	else if (key==GLFW_KEY_ESCAPE&&action==GLFW_PRESS) {
		stillGoingOn = false;
	}
}

