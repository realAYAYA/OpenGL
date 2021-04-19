#include "Framebuffers.h"
#include<iostream>

Framebuffer::Framebuffer(const GLuint& width, const GLuint& height)
{
	screenWidth = width;
	screenHeight = height;

	glGenFramebuffers(1, &fbo);
	/* By binding to the GL_FRAMEBUFFER target all the next read and write framebuffer 
	|operations will affect the currently bound framebuffer.*/
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);// GL_READ_FRAMEBUFFER | GL_DRAW_FRAMEBUFFER

	GenTextureAttachment(false, false);
	CreateRboAttachments();

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::GenTextureAttachment(GLboolean depth, GLboolean stencil)
{
	GLenum attachment_type;// What enum to use?
	if (!depth && !stencil)
		attachment_type = GL_RGB;
	else if (depth && !stencil)
		attachment_type = GL_DEPTH_COMPONENT;
	else if (!depth && stencil)
		attachment_type = GL_STENCIL_INDEX;

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	/* For this texture, we're only allocating memory and not actually filling it.
	|Also note that we do not care about any of the wrapping methods or mipmapping since we won't be needing those in most cases.*/

	if (!depth && !stencil)
		glTexImage2D(GL_TEXTURE_2D, 0, attachment_type, screenWidth, screenHeight, 0, attachment_type, GL_UNSIGNED_BYTE, NULL);
	else
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, screenWidth, screenHeight, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	/* Attach it to the framebuffer, here are following parameters:
	|target, attachment, textarget, texture, mipmap level*/
	// GL_DEPTH_ATTACHMENT | GL_STENCIL_ATTACHMENT; GL_DEPTH_COMPONENT | GL_STENCIL_INDEX
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	glBindTexture(GL_TEXTURE_2D, 0);// Set back to default
}

void Framebuffer::CreateRboAttachments()
{
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, screenWidth, screenHeight);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void Framebuffer::bind()
{
	// bind to framebuffer and draw scene as we normally would to color texture 
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glEnable(GL_DEPTH_TEST); // enable depth testing (is disabled for rendering screen-space quad)

	// make sure we clear the framebuffer's content
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Framebuffer::unbind()
{
	// now bind back to default framebuffer and draw a quad plane with the attached framebuffer color texture
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	
	// clear all relevant buffers
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // set clear color to white (not really necessary actually, since we won't be able to see behind the quad anyways)
	glClear(GL_COLOR_BUFFER_BIT);
}
