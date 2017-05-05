#pragma once
#include "Mesh.h"
#include "SOIL.h"
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

class Model{
public:
	Model();
	Model(GLchar*);
	//~Model();

	void Draw(Shader shader, GLint drawMode);
	void loadModel(string path);

	void processNode(aiNode*, const aiScene*);
	Mesh processMesh(aiMesh* mesh, const aiScene*);

	vector<Texture> loadMaterialTextures(aiMaterial*, aiTextureType,string );
	GLint TextureFromFile(const char*, string);

	vector<Mesh> meshes;
	string directory;
};

