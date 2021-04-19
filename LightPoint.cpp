#include "LightPoint.h"
#include "Shader.h"

LightPoint::LightPoint(glm::vec3 _position, glm::vec3 _color) :
	position(_position),
	color(_color)
{
	constant = 1.f;
	linear = 0.7f;
	quadratic = 1.8f;
}


