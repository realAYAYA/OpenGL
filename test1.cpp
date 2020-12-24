//#define GLEW_STATIC
//#include<iostream>
//
//#include"Shader.h"
//#include"Mesh.h"
//#include"helper.h"
//
//#include<GL/glew.h>
//#include<GLFW/glfw3.h>
//
//GLfloat triangle[] = {
//    0.5f, 0.5f, 0.0f,   // 右上角
//    0.5f, -0.5f, 0.0f,  // 右下角
//    -0.5f, -0.5f, 0.0f, // 左下角
//    -0.5f, 0.5f, 0.0f   // 左上角
//};
//
//GLuint indices[] = { // 注意索引从0开始! 
//    0, 1, 3, // 第一个三角形
//    1, 2, 3  // 第二个三角形
//};
//
//using std::cout;
//int main(int argc, char* argv[]) {
//    #pragma region Open a Window and configure
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);// Open it in MAC OS X
//
//    //Open GLFW Window
//    GLFWwindow* window = glfwCreateWindow(800, 600, "Triangle", NULL, NULL);
//    glfwMakeContextCurrent(window);
//    if (window == NULL) {
//        printf("Open window failed.\n");
//        glfwTerminate();
//        return -1;
//    }
//
//    //Init GLEW
//    glewExperimental = true;
//    if (glewInit() != GLEW_OK) {
//        printf("Init GLEW failed.\n");
//        return -1;
//    }
//
//    glViewport(0, 0, 800, 600);
//
//    /* Set mode*/
//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);// Wireframe Mode: GL_FILL/GL_LINE
//
//    cout << "Hello Triangle!\n";
//    #pragma endregion
//
//    #pragma region Init Shader Program
//    Shader* testShader = new Shader("test.vert", "test.frag");
//    #pragma endregion
//
//    #pragma region Init Models
//    vector<GLfloat> _vertices;
//    vector<GLuint> _indices;
//    for (int i = 0; i < 12; i++) {
//        _vertices.push_back(triangle[i]);
//    }
//    for (int i = 0; i < 6; i++) {
//        _indices.push_back(indices[i]);
//    }
//    Mesh Triangle(_vertices, _indices);
//    #pragma endregion
//
//    //---------------------------------------------------------------------------------------------------------------------
//    //GLuint VBO, VAO, EBO;
//    //glGenVertexArrays(1, &VAO);
//    //glGenBuffers(1, &VBO);
//    //glGenBuffers(1, &EBO);
//    //// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
//    //glBindVertexArray(VAO);
//
//    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    //glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
//
//    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
//    //glEnableVertexAttribArray(0);
//
//    //glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind
//
//    //glBindVertexArray(0);
//    //----------------------------------------------------------------------------------------------------------------------
//
//    while (!glfwWindowShouldClose(window)) {
//
//        /* Clear Screen*/
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        //----------------------------------------------------------------------------------------------------------------------
//        //testShader->use();
//        //glBindVertexArray(VAO);
//        ////glDrawArrays(GL_TRIANGLES, 0, 6);
//        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//        //glBindVertexArray(0);
//        Triangle.Draw_Array(testShader);
//        //----------------------------------------------------------------------------------------------------------------------
//        
//        /* Clean up,prepare for next render loop*/
//        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);// Tell GLFW we want to call this function on every window resize by registering it
//        glfwSwapBuffers(window);// Update window
//        glfwPollEvents();
//    }
//
//    //Exit Program
//    glfwTerminate();//End
//
//    delete testShader;
//    return 0;
//}