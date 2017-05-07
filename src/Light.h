#pragma once
#include <GL\glew.h>
#include<glm.hpp>
#include <GLFW\glfw3.h>
#include <gtc\matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shader.h"
#include "Object.h"
#include <string>
class Light{
public:
	Light(GLchar*, GLchar*, glm::vec3 , glm::vec3);
	~Light();
	void loadLightParams();
	void Draw(mat4& view, mat4& proj);

	Shader shader;
	Shader cubeShader;
	Object cubo;

	glm::vec3 color;
	glm::vec3 position;
	glm::vec3 direction;
};

