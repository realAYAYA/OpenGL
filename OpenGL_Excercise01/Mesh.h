#pragma once
#include<glm.hpp>
#include<string>
#include<vector>
#include<gl/glew.h>
#include"Shader.h"

#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture {
	unsigned int id;
	std::string type;
	aiString path;
};

class Mesh
{
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	~Mesh() {};
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	void Draw(Shader* shader);

private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};