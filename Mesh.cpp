#include "Mesh.h"
#include<iostream>
Mesh::Mesh(vector<GLfloat>const& _vertices, vector<GLuint>const& _indices)
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _vertices.size(), &_vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLfloat) * _indices.size(), &_indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

void Mesh::Draw(Shader* shader)
{
	for (unsigned int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		if (textures[i].type == "texture_diffuse")
		{
			shader->SetUniform1i("material.diffuse", i);
		}
		else if (textures[i].type == "texture_specular") {
			shader->SetUniform1i("material.specular", i);
		}
		else if (textures[i].type == "texture_reflection") {
			shader->SetUniform1i("material.specular", i);
		}
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}
	// Draw
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE0);
}

void Mesh::Draw_Array(Shader* shader)
{
	shader->use();
	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::setupMesh()
{
	// This has the advantage that when configuring vertex attribute pointers you only have to make those calls once
	// and whenever we want to draw the object, we can just bind the corresponding VAO.
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);// GL_DYNAMIC_DRAW,GL_STREAM_DRAW

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
	
	// 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(GL_FLOAT)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(GL_FLOAT)));
	
	glBindVertexArray(0);
}

/*
|	The first parameter specifies which vertex attribute we want to configure. Remember that we specified the location of 
|the position vertex attribute in the vertex shader with layout (location = 0). This sets the location of the vertex attribute 
|to 0 and since we want to pass data to this vertex attribute, we pass in 0.
|	The next argument specifies the size of the vertex attribute. The vertex attribute is a vec3 so it is composed of 3 values.
|	The third argument specifies the type of the data which is GL_FLOAT (a vec* in GLSL consists of floating point values).
|	The next argument specifies if we want the data to be normalized. If we're inputting integer data types (int, byte) and 
|we've set this to GL_TRUE, the integer data is normalized to 0 (or -1 for signed data) and 1 when converted to float. 
|This is not relevant for us so we'll leave this at GL_FALSE.
|	The fifth argument is known as the stride and tells us the space between consecutive vertex attributes. Since the next set of 
|position data is located exactly 3 times the size of a float away we specify that value as the stride. Note that since we know 
|that the array is tightly packed (there is no space between the next vertex attribute value) we could've also specified the stride 
|as 0 to let OpenGL determine the stride (this only works when values are tightly packed). Whenever we have more vertex attributes 
|we have to carefully define the spacing between each vertex attribute but we'll get to see more examples of that later on.
|	The last parameter is of type void* and thus requires that weird cast. This is the offset of where the position data begins 
|in the buffer. Since the position data is at the start of the data array this value is just 0. We will explore this parameter 
|in more detail later on
*/