#pragma once
#include<string>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using std::string;

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	string vertexString;
	string fragmentString;
	const char* vertexSource;
	const char* fragmentSource;
	unsigned int ID;		//Shader Program ID

	enum Slot {
		DIFFUSE,
		SPECULAR
	};

	void use();
	// 
	void SetUniform3f(const char* paramNameString, glm::vec3 param);
	void SetUniform1f(const char* paramNameString, float param);
	void SetUniform1i(const char* paramNameString, int slot);
private:
	// 
	void checkCompileErrors(unsigned int ID,string type);
};