#pragma once
#include<gl/glew.h>

class Framebuffers
{
public:
	Framebuffers();
	void GenTextureAttachments(GLboolean depth, GLboolean stencil);
	void CreateRboAttachments();
	void Bind();
	void DisBind();
private:
	GLuint fbo;
	GLuint texture;
	GLuint rbo;

	GLuint screenWidth, screenHeight;
};

