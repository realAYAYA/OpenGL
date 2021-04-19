#pragma once
#include<vector>
#include<string>

#include"Object.h"
#include"Mesh.h"

using std::string;

class Model :Object
{
public:
	Model(string const &path);
	~Model() {};
	
	glm::mat4 worldLocation;

	std::vector<Mesh> meshes;
	std::string directory;
	std::vector<Texture> textures_loaded;// 通过设置容器来缓存已载入的材质数据，以获得巨大优化提升

	void SetWorldLocation(const glm::mat4& modelMat);

	void Draw(Shader* shader);
	void DrawOutlining(Shader* shader, const glm::mat4& modelMat, const glm::mat4& viewMat, const glm::mat4& projMat);
private:
	void loadModel(string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial* material , aiTextureType type,
		string typeName);
	GLint TextureFromFile(const char* path, string directory);
};