#include "Light.h"
//ambiental

Light::Light( glm::vec3 pos, glm::vec3 dir ,glm::vec3 col, lightType t){
	cubeShader = Shader("./src/objectVertexShader.vertexshader", "./src/objectFragmentShader.fragmentshader");
	cubo = Object(glm::vec3(0.1f, 0.1f, 0.1f), glm::vec3(0, 0, 0), pos, Object::FigureType::cube);

	type = t;
	color = col/255.f;
	position = pos;

	direction = glm::normalize(dir);

	pLAttenuation = vec3(1, 0.35f, 0.44f);

	appertureMaxAngle = cos(glm::radians(30.f));
	appertureMinAngle = cos(glm::radians(25.f));

	switch (type){
	case ambient:
		lightShader = Shader("./src/PhongAmbientLighVertexShader.vertexshader", "./src/PhongAmbientLightFragmentShader.fragmentshader");
		break;
	case directional:
		lightShader = Shader("./src/PhongDirectionalLighVertexShader.vertexshader", "./src/PhongDirectionalLightFragmentShader.fragmentshader");
		break;
	case point:
		lightShader = Shader("./src/PhongPointLightVertexShader.vertexshader", "./src/PhongPointLightFragmentShader.fragmentshader");
		break;
	case focal:
		lightShader = Shader("./src/PhongFocalLightVertexShader.vertexshader", "./src/PhongFocalLightFragmentShader.fragmentshader");
		break;
	default:
		break;
	}
	
}

void Light::loadLightParams() {
	lightShader.USE();
	switch (type){
	case ambient:
		glUniform3f(glGetUniformLocation(lightShader.Program, "lightColor"), color.x, color.y, color.z);
		break;
	case directional:
		glUniform3f(glGetUniformLocation(lightShader.Program, "lightColor"), color.x, color.y, color.z);
		glUniform3f(glGetUniformLocation(lightShader.Program, "lightAngle"), direction.x, direction.y, direction.z);
		break;
	case point:
		glUniform3f(glGetUniformLocation(lightShader.Program, "lightColor"), color.x, color.y, color.z);
		glUniform3f(glGetUniformLocation(lightShader.Program, "lightPos"), position.x, position.y, position.z);
		glUniform3f(glGetUniformLocation(lightShader.Program, "attenFact"), pLAttenuation.x, pLAttenuation.y, pLAttenuation.z);
		break;
	case focal:
		glUniform1f(glGetUniformLocation(lightShader.Program, "appertureMax"), appertureMaxAngle);
		glUniform1f(glGetUniformLocation(lightShader.Program, "appertureMin"), appertureMinAngle);
		glUniform3f(glGetUniformLocation(lightShader.Program, "lightColor"), color.x, color.y, color.z);
		glUniform3f(glGetUniformLocation(lightShader.Program, "lightPos"), position.x, position.y, position.z);
		glUniform3f(glGetUniformLocation(lightShader.Program, "focusDir"), direction.x, direction.y, direction.z);

		break;
	default:
		break;
	}
	

}
void Light::Draw(mat4 view, mat4 proj) {
	cubeShader.USE();
	glUniformMatrix4fv(glGetUniformLocation(cubeShader.Program, "viewMat"), 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(cubeShader.Program, "projMat"), 1, GL_FALSE, glm::value_ptr(proj));

	cubo.Draw(cubeShader,color);
}
Light::~Light(){
}


