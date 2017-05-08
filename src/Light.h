#pragma once
#include <GL\glew.h>
#include<glm.hpp>
#include <GLFW\glfw3.h>
#include <gtc\matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Shader.h"
#include "Object.h"
#include <string>
#include "enums.h"
//using namespace glm;

class Light{
public:
	
	//ambiental
	Light(vec3 col);
	Light( glm::vec3 , glm::vec3, glm::vec3, lightType );
	~Light();
	void loadLightParams();
	void Draw(glm::mat4 view, glm::mat4 proj);

	Shader lightShader;
	Shader cubeShader;
	Object cubo;

	lightType type;

	glm::vec3 color;
	glm::vec3 position;
	glm::vec3 direction;
	float appertureMaxAngle;
	float appertureAnglesSeparation;
	vec3 pLAttenuation;
	
};

