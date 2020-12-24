#pragma once
#define GLEW_STATIC

#include<glm.hpp>
#include<gtc/matrix_transform.hpp>

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup);
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup);
	~Camera();

	glm::vec3 Position;
	glm::vec3 Forward;
	glm::vec3 Right;
	glm::vec3 Up;
	glm::vec3 WorldUp;
	float Pitch;
	float Yaw;
	float SenseX = 0.001f;
	float SenseY = 0.001f;
	float SpeedZ = 0;
	float SpeedX = 0;
	float SpeedY = 0;

	glm::mat4 GetViewMarix();
	void ProcessMouseMovement(float deltaX, float deltaY);
	void UpdateCameraPos();

	/* Input helper*/
	void processInput(class GLFWwindow* window);

private:
	void UpdateCameraVectors();
};