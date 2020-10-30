#include "Shader.h"
#include<iostream>
#include<fstream>
#include<sstream>//这个头文件专门用来处理string字符串的，具体查书

#include<GL/glew.h>
#include<GLFW/glfw3.h>

using std::ifstream;
using std::exception;
using std::stringstream;

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
	ifstream vertexFile;
	ifstream fragmentFile;
	stringstream vertexSStream;
	stringstream fragmentSStream;

	vertexFile.open(vertexPath);
	fragmentFile.open(fragmentPath);
	
	//防止数据提取失败或硬件出错导致打开失败，详情查看C++异常
	vertexFile.exceptions(ifstream::failbit || ifstream::badbit);
	fragmentFile.exceptions(ifstream::failbit || ifstream::badbit);

	try {
		if (!vertexFile.is_open()||!fragmentFile.is_open())
			throw exception("open file error.\n");

		//将文件流读取
		vertexSStream << vertexFile.rdbuf();
		fragmentSStream << fragmentFile.rdbuf();

		//将文件内容转换为字符串格式
		vertexString = vertexSStream.str();
		fragmentString = fragmentSStream.str();

		//可以将string字符串转换成C的字符串数组
		vertexSource = vertexString.c_str();
		fragmentSource = fragmentString.c_str();

		//编译Shader，之前学过
		unsigned int vertex, fragment;

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexSource, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentSource, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");

		// Don't forget to delete the shader objects once we've linked them into the program object
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	catch (const std::exception & ex) {
		printf(ex.what());
	}
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::checkCompileErrors(unsigned int ID, string type) {
	int success;
	char infoLog[512];

	if (type != "PROGRAM") {
		glGetShaderiv(ID, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(ID, 512, NULL, infoLog);
			std::cout << "shader compile error:" << infoLog << std::endl;
		}
	}
	else {
		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "compile program error:" << infoLog << std::endl;
		}
	}
}

void Shader::SetUniform3f(const char* paramNameString, glm::vec3 param)
{
	glUniform3f(glGetUniformLocation(ID, paramNameString), param.x, param.y, param.z);
}

void Shader::SetUniform1f(const char* paramNameString, float param)
{
	glUniform1f(glGetUniformLocation(ID, paramNameString), param);
}

void Shader::SetUniform1i(const char* paramNameString, int slot)
{
	glUniform1i(glGetUniformLocation(ID, paramNameString), slot);
}