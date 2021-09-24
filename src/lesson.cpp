#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"
#include "vbo.h"

#define GLEW_STATIC

const char* APP_TITLE = "Introduction to OpenGL - Hello Window 2";
const int WindowWidth = 800;
const int WindowHeight = 600;

void processInput(GLFWwindow *window){
    if( glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

const char* vertexFile = "../res/shaders/default.vert";
const char* fragFile = "../res/shaders/default.frag";

int main(){

    if( !glfwInit() ){
        std::cerr << "GLFW initialization failed" << std::endl;
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow *window = glfwCreateWindow(WindowWidth, WindowHeight, APP_TITLE, NULL, NULL);
    if( window == NULL ){
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glewExperimental = GL_TRUE;
    if( glewInit() != GLEW_OK ){
        std::cerr << "GLEW initialization failed" << std::endl;
        return EXIT_FAILURE;
    }

    glViewport(0,0,800,800);
    
    // shader information 
    Shader shader(vertexFile, fragFile); 
    
    
    GLfloat  vertices[] = {
        -0.50f, -0.50f, 0.00f,
         0.00f, -0.50f, 0.00f,
        -0.25f,  0.00f, 0.00f,
         0.25f,  0.00f, 0.00f,
         0.00f,  0.50f, 0.00f,
         0.50f, -0.50f, 0.00f,
    };

    GLuint indices[] = {
        0, 1, 2,
        2, 4, 3,
        3, 5, 1
    };

    // create an index for the vertex array buffer
    // the vertex buffer object and the index 
    // array buffer
    GLuint VAO, IAO;
    
    
    // generate the vertex array buffer
    glGenVertexArrays(1, &VAO);

 
    // generate the vertex buffer object
    // glGenBuffers(1, &VBO);
    VBO vbo(vertices, sizeof(vertices));
    glGenBuffers(1, &IAO);

    glBindVertexArray(VAO);
    
    // bind the buffer and describe its type
    // map the data into the buffer
    // glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    vbo.Bind();
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IAO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    while( !glfwWindowShouldClose(window) ){
        // polls for mouse events
        glfwPollEvents(); 

        processInput(window);

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //glUseProgram(shaderProgram);
        shader.Activate();
        
        
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        // double buffering for front buffer (currently shown)
        // and back buffer (current being drawn upon)
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    vbo.Delete();
    shader.Delete();

    glfwTerminate();

    return  EXIT_SUCCESS;
}
