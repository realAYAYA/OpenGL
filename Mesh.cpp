#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	setupMesh();
}

void Mesh::Draw(Shader* shader)
{
	for (unsigned int i = 0; i < textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);//�����Ӧ�������Ԫ
		if (textures[i].type == "texture_diffuse")
		{
			shader->SetUniform1i("material.diffuse", i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
		else if (textures[i].type == "texture_specular") {
			shader->SetUniform1i("material.specular", i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}
	}
	glActiveTexture(GL_TEXTURE0);

	//Draw
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), &indices[0], GL_STATIC_DRAW);
	
	// ����λ��
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// ���㷨��
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(GL_FLOAT)));
	// ������������
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(6 * sizeof(GL_FLOAT)));
	
	glBindVertexArray(0);
}

/*
ע��1
���û���������ݸ��Ƶ���ǰ�󶨵Ļ�����
���ܲ����ֱ�Ϊ�����ͣ����ݴ�С��ʵ�����ݣ��������ݷ�ʽ
GL_STREAM_DRAW�����ݽ�����һ�Σ�GPU���ʹ�ü��Ρ�
GL_STATIC_DRAW�����ݽ�����һ����ʹ�ö�Ρ�
GL_DYNAMIC_DRAW�������Ѹ��ĺܶಢ��ʹ���˺ܶ�Ρ�

ע��2
��һ������ָ������Ҫ���õĶ������ԡ����ס������ʹ��ָ���˶�����ɫ���е�λ�ö������Ե�λ��layout(location = 0)��
    ��Ὣvertex���Ե�λ������Ϊ0,������������Ҫ�����ݴ��ݸ���vertex���ԣ�������Ǵ���0��
�ڶ�������ָ���������ԵĴ�С������������vec3,�������3ֵ��ɡ�
����������ָ����������GL_FLOAT��vec* GLSL�е�a�ɸ���ֵ��ɣ���
���ĸ�����ָ���Ƿ�Ҫ�����ݽ��й淶����
    �������Ҫ���������������ͣ�int��byte������������ΪGL_TRUE�����������ݽ����淶��Ϊ0���� - 1�����з������ݣ���1��ת��Ϊfloatʱ����׼����
    ���������޹أ�������ǽ��䱣����GL_FALSE��
�����������Ϊ ���߲���������������������֮��Ŀռ䡣������һ��λ�����ݵ�λ�������Ǿ����3�������float���ǽ���ֵָ��Ϊ������
    ��ע�⣬��������֪�������ǽ������еģ���һ����������ֵ֮��û�пո񣩣����ǻ�����ָ������Ա���OpenGLȷ����ȣ�����ڽ�������ֵʱ��Ч����
    ÿ������ӵ�и��ඥ������ʱ�����Ƕ�������ϸ����ÿ����������֮��ļ�ࡣ
���һ������������void * �������Ҫ������ֵ�ת�������ǵ���λ�����ݴӻ�������ʼ��λ�á�
    ����λ������λ����������Ŀ�ͷ����˸�ֵΪ0���Ժ����ǽ�����ϸ��̽�ִ˲�����
*/