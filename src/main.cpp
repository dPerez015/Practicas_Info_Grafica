//GLEW
#define GLEW_STATIC
#include <GL\glew.h>
//GLFW
#include <GLFW\glfw3.h>
#include <iostream>
#include "Shader.h"

#include <SOIL.h>
//glm
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace std;
const GLint WIDTH = 800, HEIGHT = 600;
bool WIDEFRAME = false;
bool useLines = false;
bool stillGoingOn = true;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

float lastFrameTime;
float currentTime;
float deltaTime;
float AngularSpeed = 3.141592;
float actualAngle = 0;


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

//matrices
glm::mat4 transformMat;
//glm::mat4 translationMat;
//glm::mat4 rotationMat;
//glm::mat4 scaleMat;

glm::vec3 translateVector;
glm::vec3 scaleVector;

void flipTexture(GLfloat* arr, int offset,int stride, int count) {
	for (int i = 0; i < count; i++) {
		arr[i*stride + offset] = 1 - arr[i*stride + offset];
	}
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
	//fondo
	Color backgroundColor;
	backgroundColor.R = 1;
	backgroundColor.G = 1;
	backgroundColor.B = 0;

	//cargamos los shader
	//Shader shader("./src/SimpleVertexShader.vertexshader", "./src/SimpleFragmentShader.fragmentshader");
	Shader shader("./src/textureVertex.vertexshader", "./src/textureFragment.fragmentshader");

#pragma region Buffers
	//girar las texturas
	flipTexture(&vertices[0], 7, 8, 4);
	// Definir el buffer de vertices
	GLuint vbo, vao;
	// Definir el EBO
	GLuint ebo;
	// Crear los VBO, VAO y EBO

	//reservar memoria para el VAO, VBO y EBO
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glGenVertexArrays(1, &vao);


	glBindVertexArray(vao);
	//Establecer el objeto (VAO)
	//Declarar el VBO y el EBO
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//Establecer las propiedades de los vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
	

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//liberar el buffer de vertices
	glBindVertexArray(0);
#pragma endregion
#pragma region Texturas	
	//texturas
	GLuint texture[2];
	glGenTextures(2, texture);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	glBindTexture(GL_TEXTURE_2D, texture[1]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	
	//load a la textura
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	int width[2], height[2];
	unsigned char* image = SOIL_load_image("./src/texture.png", &width[0], &height[0], 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width[0], height[0], 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	image = SOIL_load_image("./src/texture2.jpg", &width[1], &height[1], 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width[0], height[0], 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);

#pragma endregion

#pragma region Matrices

	scaleVector=glm::vec3(0.5,-0.5,0);
	translateVector = glm::vec3(0.5,0.5,0);

	transformMat = glm::scale(transformMat, scaleVector);
	transformMat = glm::translate(transformMat, translateVector);
#pragma endregion
#pragma region Uniform Variables
	//Variables uniform

#pragma endregion

	//bucle de dibujado
	lastFrameTime = glfwGetTime();

	while (!glfwWindowShouldClose(window) && stillGoingOn) {
		currentTime = glfwGetTime();
		
		deltaTime = currentTime - lastFrameTime;
		lastFrameTime = currentTime;
		
		// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();

		//Establecer el color de fondo
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(backgroundColor.R, backgroundColor.G, backgroundColor.B, 1.0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glUniform1i(glGetUniformLocation(shader.Program, "Texture1"), 0); 
		
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		glUniform1i(glGetUniformLocation(shader.Program, "Texture2"), 1);
		
		glUniform1f(glGetUniformLocation(shader.Program, "rate"),textureMixRate );
		
		glUniformMatrix4fv(glGetUniformLocation(shader.Program,"transformMat"), 1, GL_FALSE, glm::value_ptr(transformMat));
		//establecer el shader
		shader.USE();

		//pitar el VAO
		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

		//pintar triangulos
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}
	// liberar la memoria de los VAO, EBO y VBO
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);


	// Terminate GLFW, clearing any resources allocated by GLFW.
	exit(EXIT_SUCCESS);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	//TODO, comprobar que la tecla pulsada es escape para cerrar la aplicaci�n y la tecla w para cambiar a modo widwframe
	if (key == GLFW_KEY_W&&action == GLFW_PRESS) {
		useLines = !useLines;
	}
	else if (key==GLFW_KEY_UP && (action==GLFW_PRESS || action==GLFW_REPEAT)) {
		textureMixRate += (textureChangeSpeed*deltaTime);
		
		if (textureMixRate > 1) {
			textureMixRate = 1;
		}
		//cout << deltaTime << endl;
		
	}
	else if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)) {
		textureMixRate -= (textureChangeSpeed*deltaTime*2);
		if (textureMixRate < 0) {
			textureMixRate = 0;
		}
	}
	else if (key == GLFW_KEY_ESCAPE&&action == GLFW_PRESS) {
		stillGoingOn = false;
	}
}

