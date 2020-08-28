#pragma once
#include<vector>
#include<string>
#include<iostream>
#include"Mesh.h"

#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

using std::string;

class Model
{
public:
	Model(string const &path);
	~Model() {};

	std::vector<Mesh> meshes;
	std::string directory;
	void Draw(Shader* shader);
private:
	std::vector<Texture> textures_loaded;//通过设置容器来缓存已载入的材质数据，以获得巨大优化提升
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* material , aiTextureType type,
		string typeName);
};