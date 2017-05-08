#include "Object.h"
Object::Object() {}
Object::Object(vec3 scal, vec3 rot, vec3 pos, vec3 col ,FigureType typef) {
	color = col/255.f;
	ambiental = 0.1;
	specular = 0.5;
	specularExp = 32;
	speed = 2;
	GLfloat VertexBufferObject[] = {
		//front
		1.0f ,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
		1.0f , -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
		1.0f ,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
		//back
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		1.0f , -1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		1.0f ,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f,

		1.0f ,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
		//left
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
		//right
		1.0f , -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
		1.0f ,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
		1.0f ,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,

		1.0f ,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
		1.0f , -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
		1.0f , -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
		//down
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
		1.0f , -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
		1.0f , -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
		1.0f , -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
		-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
		//up
		1.0f ,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		1.0f ,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		1.0f ,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f
	};

#pragma region Buffers

	glGenVertexArrays(1,&VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1,&EBO);

	glBindVertexArray(VAO); {
		glBindBuffer(GL_ARRAY_BUFFER,VBO);
		switch (typef) {
		case Object::cube:
			glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferObject), &VertexBufferObject[0], GL_STATIC_DRAW);
			
			//posiciones
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE,6*sizeof(GLfloat), (GLvoid*)0);
			//normales
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),(GLvoid*)(3 * sizeof(GLfloat)));

			break;
		default:
			break;
		}

		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}glBindVertexArray(0);
#pragma endregion
	
#pragma region Transform
	position = pos;
	scale = scal;
	rotation = rot;
#pragma endregion

	
}


Object::~Object() {}

void Object::Draw(Shader shader, lightType t) {
	shader.USE();
	glUniformMatrix4fv(glGetUniformLocation(shader.Program, "transformMat"), 1, GL_FALSE, glm::value_ptr(GetModelMatrix()));
	switch (t){
	case ambient:
		glUniform1f(glGetUniformLocation(shader.Program, "ambInt"), ambiental);
		glUniform3f(glGetUniformLocation(shader.Program, "ObjectColor"), color.x, color.y, color.z);
		break;
	case directional:
		glUniform1f(glGetUniformLocation(shader.Program, "ambInt"), ambiental);
		glUniform1f(glGetUniformLocation(shader.Program, "specInt"), specular);
		glUniform1f(glGetUniformLocation(shader.Program, "Ke"), specularExp);
		glUniform3f(glGetUniformLocation(shader.Program, "ObjectColor"), color.x, color.y, color.z);
		break;
	case point:
		glUniform1f(glGetUniformLocation(shader.Program, "ambInt"), ambiental);
		glUniform1f(glGetUniformLocation(shader.Program, "specInt"), specular);
		glUniform1f(glGetUniformLocation(shader.Program, "Ke"), specularExp);
		glUniform3f(glGetUniformLocation(shader.Program, "ObjectColor"), color.x, color.y, color.z);
		break;
	case focal:
		glUniform1f(glGetUniformLocation(shader.Program, "ambInt"), ambiental);
		glUniform1f(glGetUniformLocation(shader.Program, "specInt"), specular);
		glUniform1f(glGetUniformLocation(shader.Program, "Ke"), specularExp);
		glUniform3f(glGetUniformLocation(shader.Program, "ObjectColor"), color.x, color.y, color.z);
		break;
	default:
		break;
	}

	
	glBindVertexArray(VAO);
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}
void Object::Move(vec3 translation) {
	position += translation;
}
void Object::Rotate(vec3 rota) {
	rotation += rota;
}
void Object::Scale(vec3 scal) {
	scale = scal;
}

void Object::doMovement(GLFWwindow* window, GLfloat delta) {
	if (glfwGetKey(window, GLFW_KEY_KP_2)==GLFW_PRESS) moveStates[0] = true;
	else if (glfwGetKey(window, GLFW_KEY_KP_2) == GLFW_RELEASE)moveStates[0] = false;

	if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_PRESS)moveStates[1] = true;
	else if (glfwGetKey(window, GLFW_KEY_KP_8) == GLFW_RELEASE)moveStates[1] = false;

	if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_PRESS)moveStates[2] = true;
	else if (glfwGetKey(window, GLFW_KEY_KP_4) == GLFW_RELEASE)moveStates[2] = false;

	if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_PRESS)moveStates[3] = true;
	else if (glfwGetKey(window, GLFW_KEY_KP_6) == GLFW_RELEASE)moveStates[3] = false;

	nextMove = glm::vec3(0,0,0);
	if (moveStates[0]) { nextMove.y -= speed; }
	if (moveStates[1]) { nextMove.y += speed; }
	if (moveStates[2]) { nextMove.x -= speed; }
	if (moveStates[3]) { nextMove.x += speed; }
	nextMove *= delta;

	Move(nextMove);
}

mat4 Object::GetModelMatrix() {
	glm::mat4 model;
	model = glm::translate(model, position);

	model = glm::rotate(model, rotation.x, vec3(1, 0, 0));
	model = glm::rotate(model, rotation.y, vec3(0, 1, 0));
	model = glm::rotate(model, rotation.z, vec3(0, 0, 1));

	model = glm::scale(model, scale);

	return model;
}

vec3 Object::GetPosition() {
	return position;
}

void Object::Delete() {
	//glDeleteBuffers(1,&VBO);
	//glDeleteBuffers(1,&EBO);
	//glDeleteBuffers(1, &VAO);

}
