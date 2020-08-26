#define STB_IMAGE_IMPLEMENTATION//注释1
#include<iostream>

#include "stb_image.h"//一个非常流行的单头文件图像加载库，它能够加载大部分流行的文件格式

//glm库是数学函库
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using std::cout;
using std::endl;

int main2() {
	glm::vec4 vec(1.0f, 0, 0, 1.0f);

	//4元矩阵
	glm::mat4 trans;//trans will be a identity 4x4 matrix
	trans = glm::translate(trans, glm::vec3(2.0f, 0, -1.0f));//位移变换

	vec = trans * vec;
	cout << vec.x << vec.y << vec.z << endl;
	return 0;
}

/*注释1
通过定义STB_IMAGE_IMPLEMENTATION，预处理器会修改头文件，
让其只包含相关的函数定义源码，
等于是将这个头文件变为一个.cpp 文件了*/