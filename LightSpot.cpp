#include "LightSpot.h"
#include "Shader.h"

LightSpot::LightSpot(std::string _name, glm::vec3 _position, glm::vec3 _angles, glm::vec3 _color) :
	position(_position),
	angles(_angles),
	color(_color)
{
	constant = 1.f;
	linear = 0.09f;
	quadratic = 0.032f;
	name = _name;
	UpdateDirection();
}

void LightSpot::UpdateDirection()
{
	direction = glm::vec3(0, 0, 1.0f);//pointing to Z(worldup)
	direction = glm::rotateZ(direction, angles.z);
	direction = glm::rotateX(direction, angles.x);
	direction = glm::rotateY(direction, angles.y);
	direction = -1.0f * direction;
}

void LightSpot::active(Shader* shader)const
{
	shader->setVec3((name + std::string(".pos")).c_str(), position);
	shader->setVec3((name + std::string(".dirToLight")).c_str(), direction);
	shader->setVec3((name + std::string(".color")).c_str(), color);
	shader->setFloat((name + std::string(".linear")).c_str(), linear);
	shader->setFloat((name + std::string(".constant")).c_str(), constant);
	shader->setFloat((name + std::string(".quadratic")).c_str(), quadratic);
	shader->setFloat((name + std::string(".cosPhyInner")).c_str(), cosPhyInner);
	shader->setFloat((name + std::string(".cosPhyOutter")).c_str(), cosPhyOutter);
	//glUniform3f(glGetUniformLocation(ModelShader->ID, "lightS.pos"), lightS.position.x, lightS.position.y, lightS.position.z);
	//glUniform3f(glGetUniformLocation(ModelShader->ID, "lightS.dirToLight"), lightS.direction.x, lightS.direction.y, lightS.direction.z);
	//glUniform3f(glGetUniformLocation(ModelShader->ID, "lightS.color"), lightS.color.x, lightS.color.y, lightS.color.z);
	//glUniform1f(glGetUniformLocation(ModelShader->ID, "lightS.linear"), lightS.linear);
	//glUniform1f(glGetUniformLocation(ModelShader->ID, "lightS.constant"), lightS.constant);
	//glUniform1f(glGetUniformLocation(ModelShader->ID, "lightS.quadratic"), lightS.quadratic);
	//glUniform1f(glGetUniformLocation(ModelShader->ID, "lightS.cosPhyInner"), lightS.cosPhyInner);
	//glUniform1f(glGetUniformLocation(ModelShader->ID, "lightS.cosPhyOutter"), lightS.cosPhyOutter);
}

