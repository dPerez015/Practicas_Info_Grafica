#pragma once
#include <GL\glew.h>
#include<glm.hpp>
#include <GLFW\glfw3.h>
#include <gtc\matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shader.h"
#include "enums.h"

using namespace glm;


class Object {

public:
	enum FigureType {
		cube = 0,
	};
	Object();
	Object(vec3 scale, vec3 rotation, vec3 position, vec3 color,FigureType typef);
	~Object();

	void Draw(Shader, lightType);
	void Move(vec3 translation);
	void Rotate(vec3 rota);
	void Scale(vec3 scal);
	void doMovement(GLFWwindow*, GLfloat);
	void Delete();
	mat4 GetModelMatrix();
	vec3 GetPosition();

private:
	GLuint VBO, VAO, EBO;
	vec3 position;
	vec3 scale;
	vec3 rotation;
	//luz
	vec3 color;
	float specular;
	float specularExp;
	float ambiental;

	//movimiento por teclado
	bool moveStates[4];
	vec3 nextMove;
	float speed;
};

