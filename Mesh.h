#pragma once
#include<glm.hpp>
#include<string>
#include<vector>

#include<gl/glew.h>

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

using std::vector;

class Shader;
class Mesh
{
public:
	Mesh() {};
	Mesh(vector<GLfloat> const& _vertices, vector<GLuint> const& _indices);
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures);
	~Mesh();
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Texture> textures;

	void Draw(Shader* shader);
	void Draw_Array(Shader* shader);

private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};