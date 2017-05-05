#include "Object.h"
//
//Object::Object(vec3 scal, vec3 rot, vec3 pos, FigureType typef) {
//	GLfloat VertexBufferObject[] = {
//		//front
//		1.0f ,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
//		1.0f , -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
//		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
//		-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
//		-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
//		1.0f ,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f,
//		//back
//		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
//		1.0f , -1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
//		1.0f ,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
//
//		1.0f ,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
//		-1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
//		-1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f,
//		//left
//		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
//		-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
//		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
//		-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f,
//		-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
//		-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f,
//		//right
//		1.0f , -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
//		1.0f ,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
//		1.0f ,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
//
//		1.0f ,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
//		1.0f , -1.0f,  1.0f,  1.0f,  0.0f,  0.0f,
//		1.0f , -1.0f, -1.0f,  1.0f,  0.0f,  0.0f,
//		//down
//		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
//		1.0f , -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
//		1.0f , -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
//		1.0f , -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
//		-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f,
//		-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f,
//		//up
//		1.0f ,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
//		1.0f ,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//		-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f,
//		-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f,
//		1.0f ,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f
//	};
//
//#pragma region Buffers
//
//	glGenVertexArrays(1,&VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1,&EBO);
//
//	glBindVertexArray(VAO); {
//		glBindBuffer(GL_ARRAY_BUFFER,VBO);
//		switch (typef) {
//		case Object::cube:
//			glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBufferObject), &VertexBufferObject[0], GL_STATIC_DRAW);
//			
//			//posiciones
//			glEnableVertexAttribArray(0);
//			glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE,6*sizeof(GLfloat), (GLvoid*)0);
//			//normales
//			glEnableVertexAttribArray(1);
//			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)3 * sizeof(GLfloat));
//
//			break;
//		default:
//			break;
//		}
//
//		glBindBuffer(GL_ARRAY_BUFFER, 0);
//	}glBindVertexArray(0);
//#pragma endregion
//	
//#pragma region Transform
//	position = pos;
//	scale = scal;
//	rotation = rot;
//#pragma endregion
//
//	
//
//}
//
//
//Object::~Object() {}
//
//void Object::Draw() {
//
//}
//void Object::Move(vec3 translation) {
//	position += translation;
//}
//void Object::Rotate(vec3 rota) {
//	rotation += rota;
//}
//void Object::Scale(vec3 scal) {
//	scale = scal;
//}
//
//mat4 Object::GetModelMatrix() {
//
//}
//
//vec3 Object::GetPosition() {
//	return position;
//}
//
//void Object::Delete() {
//
//}
