/*
|图形场景中的必要的全局变量和方法在此声明实现
*/
#pragma once
#include<iostream>
#include"SOIL.h"// Load .obj files
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include"Camera.h"

float lastX, lastY;
bool firstMouse = true;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

#pragma region Camera Declare
Camera camera(glm::vec3(0, 0, 30.0f), glm::radians(-15.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));
#pragma endregion

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void mouse_callback(class GLFWwindow* window, double xPos, double yPos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

unsigned int LoadImageToGPU(const char* filename);

float lerp(float a, float b, float f);// Accelerating interpolation function

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xPos, double yPos)
{
    if (firstMouse) {
        lastX = xPos;
        lastY = yPos;
        firstMouse = false;
    }
    float deltaX, deltaY;

    deltaX = xPos - lastX;
    deltaY = yPos - lastY;

    lastX = xPos;
    lastY = yPos;

    camera.ProcessMouseMovement(deltaX, deltaY);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

unsigned int LoadImageToGPU(const char* filename) {
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);

	int width, height, nrComponents;
	unsigned char* data = SOIL_load_image(filename, &width, &height, &nrComponents, 0);
	if (data) {
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA; //GL_SRGB;

		glBindTexture(GL_TEXTURE_2D, TexBuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else {
		std::cout << "Image load failed: " << filename << std::endl;
	}
	SOIL_free_image_data(data);
	glBindTexture(GL_TEXTURE_2D, 0);
	return TexBuffer;
}


float lerp(float a, float b, float f)
{
	return a + f * (b - a);
}