#pragma once
#include <GL\glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
//GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);
class Shader {
public:
	Shader();
	Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
	GLuint Program;
	void USE();
};


