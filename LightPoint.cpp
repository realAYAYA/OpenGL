#include "LightPoint.h"

LightPoint::LightPoint(glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) :
	position(_position),
	angles(_angles),
	color(_color)
{
	constant = 1.f;
	linear = 0.09f;
	quadratic = 0.032f;
}

void LightPoint::UpdateDirection()
{
	direction = glm::vec3(0, 0, 1.0f);//pointing to Z(worldup)
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateX(direction, angles.x);
	direction = glm::rotateY(direction, angles.y);
	direction = -1.0f * direction;
}