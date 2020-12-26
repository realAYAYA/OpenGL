#pragma once
#include<string>
class Shader;
class Light
{
public:
	std::string name;
	virtual void active(Shader* shader)const {} 
};