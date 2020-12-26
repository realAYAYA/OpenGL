#define GLEW_STATIC
#include<iostream>

#include"Shader.h"
#include"Camera.h"
#include"Material.h"
#include"LightDirectional.h"
#include"LightPoint.h"
#include"LightSpot.h"
#include"Mesh.h"
#include"Model.h"
#include"Skybox.h"
#include"helper.h"

#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>


using std::cout;
using std::endl;

#pragma region Model Data
float vertices[] = {
    // positions          // normals           // texture coords
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
     0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
    -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
     0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
     0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
     0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
     0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};
GLfloat skyboxVertices[] = {
    // Positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};
#pragma endregion

#pragma region Light Declare
LightDirectional lightD(std::string("lightD"), glm::vec3(1.0f, 1.0f, -1.0f),
    glm::vec3(glm::radians(90.0f), glm::radians(0.0f), 0),
    glm::vec3(1.0f, 1.0, 1.0f));
LightPoint lightP0(std::string("lightP0"),glm::vec3(1.0f, 0, 0), 
    glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
    glm::vec3(1.0f, 0, 0));
LightPoint lightP1(std::string("lightP1"), glm::vec3(0, 1.0f, 0),
    glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
    glm::vec3(0, 1.0f, 0));
LightPoint lightP2(std::string("lightP2"), glm::vec3(0, 0, 1.0f),
    glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
    glm::vec3(0, 0, 1.0f));
LightPoint lightP3(std::string("lightP3"), glm::vec3(1.0f, 1.0f, 1.0f),
    glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0),
    glm::vec3(1.0f, 1.0f, 1.0f));
LightSpot lightS(std::string("lightS"), glm::vec3(0, 5.0f, 0),
    glm::vec3(glm::radians(90.0f), glm::radians(0.0f), 0),
    glm::vec3(10.0f, 10.0f, 10.0f));
#pragma endregion

int main(int argc,char *argv[]) {
    #pragma region Open a Window and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);// Open it in MAC OS X

    //Open GLFW Window
    GLFWwindow* window = glfwCreateWindow(800, 600, "My OpenGL Game", NULL, NULL);
    if (window == NULL) {
        printf("Open window failed.\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    //Init GLEW
    glewExperimental = true;
    if (glewInit() != GLEW_OK) {
        printf("Init GLEW failed.\n");
        return -1;
    }

    glViewport(0, 0, 800, 600);
    cout << "Hello OpenGL!\n";

    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_BACK);// GL_FRONT
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Set the required callback functions
    glfwSetCursorPosCallback(window, mouse_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    #pragma endregion


    #pragma region Init Shader Program
    Shader* ModelShader = new Shader("vertexSource.vert", "fragmentSource.frag");
    Shader* skyboxShader = new Shader("skybox.vert", "skybox.frag");
    #pragma endregion

    #pragma region Init Material
    Material* myMaterial = new Material(ModelShader,
        LoadImageToGPU("container2.png", GL_RGBA, GL_RGBA, Shader::DIFFUSE),
        LoadImageToGPU("container2_specular.png", GL_RGBA, GL_RGBA, Shader::SPECULAR),
        glm::vec3(1.0f, 1.0f, 1.0f),
        32.0f);
    #pragma endregion

    #pragma region Init Models
    std::string exePath = argv[0];
    Model model(exePath.substr(0, exePath.find_last_of('\\')) + "\\model\\nanosuit.obj");
    std::vector<string> faces;
    faces.push_back(exePath.substr(0, exePath.find_last_of('\\')) + "\\skybox\\right.jpg");
    faces.push_back(exePath.substr(0, exePath.find_last_of('\\')) + "\\skybox\\left.jpg");
    faces.push_back(exePath.substr(0, exePath.find_last_of('\\')) + "\\skybox\\top.jpg");
    faces.push_back(exePath.substr(0, exePath.find_last_of('\\')) + "\\skybox\\bottom.jpg");
    faces.push_back(exePath.substr(0, exePath.find_last_of('\\')) + "\\skybox\\back.jpg");
    faces.push_back(exePath.substr(0, exePath.find_last_of('\\')) + "\\skybox\\front.jpg");
    std::vector<GLfloat> _vertices;
    for (int i = 0; i < 108; i++) {
        _vertices.push_back(skyboxVertices[i]);
    }
    Skybox skybox(_vertices, faces);
    #pragma endregion

    #pragma region Prepare MVP matrices
    /* Calculate our transformation matrix here*/
    glm::mat4 modelMat;
    glm::mat4 viewMat;
    glm::mat4 projMat;
    /* 
    |Due to perspective the lines seem to coincide at a far enough distance.
    |This is exactly the effect perspective projection tries to mimic and it does so using a perspective projection matrix.
    |The projection matrix maps a given frustum range to clip space, but also manipulates the w value of each vertex coordinate
    |in such a way that the further away a vertex coordinate is from the viewer, the higher this w component becomes.
    |Its first parameter defines the fov value, that stands for field of view and sets how large the viewspace is.
    |The second parameter sets the aspect ratio which is calculated by dividing the viewport's width by its height.
    |The third and fourth parameter set the near and far plane of the frustum. Usually set 0.1 and 100.0.
    */
    projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    #pragma endregion

    while (!glfwWindowShouldClose(window)) {
        camera.processInput(window);// Process Input linsenter
        glfwPollEvents();
        /* Clear Screen*/
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        viewMat = camera.GetViewMarix();

        for (int i = 0; i < 1; i++) {
            /* Set View and Projection Matrices here if you want*/
            //modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);// Set Model matrix
            ModelShader->use();
            ModelShader->SetUniform4f("modelMat", modelMat);
            ModelShader->SetUniform4f("viewMat", viewMat);
            ModelShader->SetUniform4f("projMat", projMat);

            /* Camera position*/
            ModelShader->SetUniform3f("cameraPos", camera.Position);

            #pragma region Lights
            glUniform3f(glGetUniformLocation(ModelShader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
            glUniform3f(glGetUniformLocation(ModelShader->ID, "ambienColor"), 0.1f, 0.1f, 0.1f);
            
            lightD.active(ModelShader);
            lightP0.active(ModelShader);
            lightP1.active(ModelShader);
            lightP2.active(ModelShader);
            lightP3.active(ModelShader);
            lightS.active(ModelShader);
            #pragma endregion

            //myMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
            //myMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);
            //myMaterial->shader->SetUniform3f("material.ambient", myMaterial->ambient);
            myMaterial->shader->SetUniform1f("material.shininess", myMaterial->shininess);

            model.Draw(myMaterial->shader);
            skybox.Draw(skyboxShader, viewMat, projMat);
        }
        
        camera.UpdateCameraPos();

        /* Clean up,prepare for next render loop*/
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);// Tell GLFW we want to call this function on every window resize by registering it
        glfwSwapBuffers(window);// Update window
    }

    //Exit Program
    glfwTerminate();// End

    delete ModelShader;
    delete skyboxShader;
    return 0;
}