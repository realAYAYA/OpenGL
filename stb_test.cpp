#define STB_IMAGE_IMPLEMENTATION//ע��1
#include<iostream>

#include "stb_image.h"//һ���ǳ����еĵ�ͷ�ļ�ͼ����ؿ⣬���ܹ����ش󲿷����е��ļ���ʽ

//glm������ѧ����
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using std::cout;
using std::endl;

int main2() {
	glm::vec4 vec(1.0f, 0, 0, 1.0f);

	//4Ԫ����
	glm::mat4 trans;//trans will be a identity 4x4 matrix
	trans = glm::translate(trans, glm::vec3(2.0f, 0, -1.0f));//λ�Ʊ任

	vec = trans * vec;
	cout << vec.x << vec.y << vec.z << endl;
	return 0;
}

/*ע��1
ͨ������STB_IMAGE_IMPLEMENTATION��Ԥ���������޸�ͷ�ļ���
����ֻ������صĺ�������Դ�룬
�����ǽ����ͷ�ļ���Ϊһ��.cpp �ļ���*/