#pragma once
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "Shader.h"
#include <GL\glew.h>
#include <gtc\matrix_transform.hpp>
#include <glm.hpp>
#include <assimp\types.h>
using namespace std;

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};
struct Texture {
	GLuint id;
	string type;
	aiString path;
};
class Mesh{
public:
	Mesh(vector<Vertex> , vector<GLuint>, vector<Texture> );
	//~Mesh();

	
	void Draw(Shader MeshShader, GLint DrawMode);

	vector<Vertex> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;
private:
	GLuint VAO, VBO, EBO;
	void setupMesh();
};

