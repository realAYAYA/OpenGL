#include "Model.h"
//#include"stb_image.h"
#include<iostream>
#include"SOIL.h"

Model::Model(string const& path)
{
	loadModel(path);
}

void Model::Draw(Shader* shader)
{
	//shader->use();
	for (unsigned int i = 0; i < meshes.size(); i++) {
		meshes[i].Draw(shader);
	}
}

void Model::loadModel(string path)
{
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	directory = path.substr(0, path.find_last_of('\\'));// Take model's root path
	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
	// 
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* curMesh = scene->mMeshes[node->mMeshes[i]];// Actrully,it is just a pointer
		meshes.push_back(processMesh(curMesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
	std::vector<Vertex> tempVertices;
	std::vector<unsigned int> tempIndices;
	std::vector<Texture> tempTexture;

	glm::vec3 tempVec;
	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex tempVertex;
		tempVertex.Position.x = mesh->mVertices[i].x;
		tempVertex.Position.y = mesh->mVertices[i].y;
		tempVertex.Position.z = mesh->mVertices[i].z;
		
		tempVertex.Normal.x = mesh->mNormals[i].x;
		tempVertex.Normal.y = mesh->mNormals[i].y;
		tempVertex.Normal.z = mesh->mNormals[i].z;

		if (mesh->mTextureCoords[0])
		{
			tempVertex.TexCoords.x = mesh->mTextureCoords[0][i].x;
			tempVertex.TexCoords.y = mesh->mTextureCoords[0][i].y;
		}
		else {
			tempVertex.TexCoords = glm::vec2(0, 0);
		}
		tempVertices.push_back(tempVertex);
	}
	
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {// "face" is just mean "Indices",uesd to draw triangles
		for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++) {
			tempIndices.push_back(mesh->mFaces[i].mIndices[j]);
		}
	}
	
	// Set MaterialTextures
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<Texture> diffuseMaps = this->loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		tempTexture.insert(tempTexture.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<Texture> specularMaps = this->loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		tempTexture.insert(tempTexture.end(), specularMaps.begin(), specularMaps.end());
	}

	return Mesh(tempVertices, tempIndices, tempTexture);// 
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial* material, aiTextureType type, string typeName)
{
	std::vector<Texture> textures;
	for (unsigned int i = 0; i < material->GetTextureCount(type); i++) {
		aiString str;
		material->GetTexture(type, i, &str);
		GLboolean skip = false;
		for (unsigned j = 0; j < textures_loaded.size(); j++) {
			if (textures_loaded[j].path == str) {// 
				textures.push_back(textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip) {// 
			Texture texture;
			texture.id = TextureFromFile(str.C_Str(), this->directory);// 
			texture.type = typeName;
			texture.path = str;
			textures.push_back(texture);
			textures_loaded.push_back(texture);
		}
	}
	return textures;
}

GLint Model::TextureFromFile(const char* path, string directory)
{
	// Generate texture ID and load texture data 
	string filename = string(path);
	filename = directory + '\\' + filename;
	GLuint textureID;
	glGenTextures(1, &textureID);// Assign texture to ID

	int width, height;
	unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
	if (image) {
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else{
		std::cout << "Load image filed.\n";
	}

	// Parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Texture filtering can be set for magnifying and minifying operations (when scaling up or downwards) 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	SOIL_free_image_data(image);
	glBindTexture(GL_TEXTURE_2D, 0);
	return textureID;
}