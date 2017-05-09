#pragma once
#define GLEW_STATIC
#include <GL\glew.h>
#include <SOIL.h>
#include "Shader.h"

class Material{

public:
	Material();
	Material(char *DiffPath, char*SpectPath, float Shini);
	~Material();
	void SetMaterial(Shader &had);
	void ActivateTextures();
	void SetShininess(Shader &shad);
private:
	GLuint TextDiff, TextSpec;
	float Shininess;

};

