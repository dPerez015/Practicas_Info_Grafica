#pragma once
#include <GL\glew.h>
#include<glm.hpp>
#include <GLFW\glfw3.h>
#include <gtc\matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shader.h"
#include "enums.h"
#include "material.h"
using namespace glm;


class Object {

public:
	enum FigureType {
		cube = 0,
	};
	Object();
	Object(vec3 scale, vec3 rotation, vec3 position,FigureType typef);
	Object(vec3 scale, vec3 rotation, vec3 position, char* diffPath,char*specPath, float shinny,FigureType typef);

	~Object();

	void Draw(Shader, vec3 color);
	void Draw(Shader);
	void Move(vec3 translation);
	void Rotate(vec3 rota);
	void Scale(vec3 scal);
	void doMovement(GLFWwindow*, GLfloat);
	void Delete();
	mat4 GetModelMatrix();
	vec3 GetPosition();
	Material material;
private:
	GLuint VBO, VAO, EBO;
	vec3 position;
	vec3 scale;
	vec3 rotation;
	//luz
	
	//movimiento por teclado
	bool moveStates[6];
	vec3 nextMove;
	float speed;
};

