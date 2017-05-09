#include "material.h"
Material::Material() {}

Material::Material(char *DiffPath, char*SpectPath, float Shini){
	Shininess = Shini;
	//soil 
	int diffWidth, diffHeight;
	unsigned char* diffImage = SOIL_load_image(DiffPath, &diffWidth, &diffHeight, 0, SOIL_LOAD_RGB);
	int specWidth, specHeight;
	unsigned char* specImage = SOIL_load_image(SpectPath, &specWidth, &specHeight,0,SOIL_LOAD_RGB);
	
	//generado de texturas
	glGenTextures(1,&TextDiff);
	glBindTexture(GL_TEXTURE_2D, TextDiff);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,diffWidth,diffHeight,0, GL_RGB,GL_UNSIGNED_BYTE, diffImage);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &TextSpec);
	glBindTexture(GL_TEXTURE_2D, TextSpec);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, specWidth, specHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, specImage);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SOIL_free_image_data(diffImage);
	SOIL_free_image_data(specImage);
	glBindTexture(GL_TEXTURE_2D,0);
	
}


Material::~Material(){
}

void Material::SetMaterial(Shader &shader) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextDiff);
	glUniform1i(glGetUniformLocation(shader.Program, "material.diffuse"), 0);
	
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TextSpec);
	glUniform1i(glGetUniformLocation(shader.Program, "material.specular"), 1);

}

void Material::SetShininess(Shader &shader) {
	
	glUniform1f(glGetUniformLocation(shader.Program, "material.shininess"), Shininess);

}

void Material::ActivateTextures() {
	
	
}
