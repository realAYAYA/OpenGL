#include "LightDirectional.h"
#include "Shader.h"

LightDirectional::LightDirectional(std::string _name, glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) :
	position(_position),
	angles(_angles),
	color(_color)
{
	name = _name;
	UpdateDirection();
}

void LightDirectional::UpdateDirection() {
	direction = glm::vec3(0, 0, 1.0f);//pointing to Z(worldup)
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateX(direction, angles.x);
	direction = glm::rotateY(direction, angles.y);
	direction = -1.0f * direction;
}

void LightDirectional::active(Shader* shader)const
{
	shader->SetUniform3f((name + std::string(".pos")).c_str(), position);
	shader->SetUniform3f((name + std::string(".dirToLight")).c_str(), direction);
	shader->SetUniform3f((name + std::string(".color")).c_str(), color);
}
