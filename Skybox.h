#pragma once
#include<glm.hpp>
#include<string>
#include<vector>
#include<gl/glew.h>
#include"Shader.h"

#include<assimp/Importer.hpp>
#include<assimp/scene.h>
#include<assimp/postprocess.h>
class Skybox
{
public:
	Skybox(GLfloat const vertices[], std::vector<string>& faces);// Draw Array,CubemapTexture
	GLuint LoadCubemap(std::vector<string>& faces);
	void Draw(Shader* shader, glm::mat4 const& view, glm::mat4 const& projection);
	~Skybox() {};
private:
	GLuint cubemapTexture;// If possible.
	unsigned int VAO, VBO;
};

