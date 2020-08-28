#pragma once

#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
#include<gtx/rotate_vector.hpp>//����������ת�Ŀ�

class LightPoint
{
public:
	LightPoint(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color = glm::vec3(1.0f, 1.0f, 1.0f));
	~LightPoint() {};

	glm::vec3 position;//ƽ�йⲻ��Ҫλ��
	glm::vec3 angles;
	glm::vec3 direction = glm::vec3(0, 0, 1.0f);
	glm::vec3 color;

	void UpdateDirection();

	float constant = 1.0f;
	float linear = 0.7f;
	float quadratic = 0.001f;
};

