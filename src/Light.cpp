#include "Light.h"



Light::Light(GLchar* vertex, GLchar* fragment, glm::vec3 pos, glm::vec3 col)
	:	shader(Shader(vertex, fragment)),
		cubeShader(Shader("./src/objectVertexShader.vertexshader", "./src/objectFragmentShader.fragmentshader")),
		cubo(Object(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0, 0, 0), pos, col, Object::FigureType::cube))
{
	color = col/255.f;
	position = pos;
	
}

void Light::loadLightParams() {
	
	glUniform3f(glGetUniformLocation(shader.Program, "lightColor"), color.x, color.y, color.z);
	 
}
void Light::Draw(mat4& view, mat4& proj) {
	glUniform3f(glGetUniformLocation(cubeShader.Program, "ObjectColor"), color.x, color.y, color.z);
	glUniformMatrix4fv(glGetUniformLocation(cubeShader.Program, "viewMat"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(cubeShader.Program, "projMat"), 1, GL_FALSE, glm::value_ptr(proj));

	cubo.Draw(shader);
}
Light::~Light(){
}


