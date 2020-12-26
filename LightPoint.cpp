#include "LightPoint.h"
#include "Shader.h"

LightPoint::LightPoint(std::string _name, glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) :
	position(_position),
	angles(_angles),
	color(_color)
{
	constant = 1.f;
	linear = 0.09f;
	quadratic = 0.032f;
	name = _name;
}

void LightPoint::UpdateDirection()
{
	direction = glm::vec3(0, 0, 1.0f);//pointing to Z(worldup)
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateX(direction, angles.x);
	direction = glm::rotateY(direction, angles.y);
	direction = -1.0f * direction;
}

void LightPoint::active(Shader* shader) const
{
	shader->SetUniform3f((name + std::string(".pos")).c_str(), position);
	shader->SetUniform3f((name + std::string(".dirToLight")).c_str(), direction);
	shader->SetUniform3f((name + std::string(".color")).c_str(), color);
	shader->SetUniform1f((name + std::string(".linear")).c_str(), linear);
	shader->SetUniform1f((name + std::string(".constant")).c_str(), constant);
	shader->SetUniform1f((name + std::string(".quadratic")).c_str(), quadratic);
}
