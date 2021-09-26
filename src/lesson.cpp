#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"
#include "vbo.hpp"
#include "iao.hpp"
#include "vao.hpp"

#define GLEW_STATIC

const char* APP_TITLE = "Introduction to OpenGL - Hello Window 4";

void processInput(GLFWwindow *window){
    if( glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


const char* vertexFile = "../res/shaders/default.vert";
const char* fragFile = "../res/shaders/default.frag";

const unsigned int width = 800;
const unsigned int height = 600;

GLfloat  vertices[] = {
    //    coordinates     /     colors
    -0.50f, -0.50f, 0.00f, 0.8f, 0.30f, 0.02f,
     0.00f, -0.50f, 0.00f, 0.8f, 0.30f, 0.02f,
    -0.25f,  0.00f, 0.00f, 1.0f, 0.60f, 0.32f,
     0.25f,  0.00f, 0.00f, 0.9f, 0.45f, 0.17f,
     0.00f,  0.50f, 0.00f, 0.9f, 0.45f, 0.17f,
     0.50f, -0.50f, 0.00f, 0.8f, 0.30f, 0.02f,
};

GLuint indices[] = {
    0, 1, 2,
    2, 4, 3,
    3, 5, 1
};


int main(){
    
    if( !glfwInit() ){
        std::cerr << "GLFW initialization failed" << std::endl;
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    GLFWwindow *window = glfwCreateWindow(width, height, APP_TITLE, NULL, NULL);
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

    glViewport(0,0,width,height);

    // shader information 
    Shader shader(vertexFile, fragFile); 
    shader.Bind();

    // setting up shader uniform
    GLfloat r = 0.0f;
    GLfloat increment = 0.05f;

    // create an index for the vertex array buffer
    VAO vao;
    vao.Bind();

    // generate the vertex buffer object 
    // and index array objects
    VBO vbo(vertices, sizeof(vertices));
    IAO iao(indices, sizeof(indices));

    // link attribute for the vertex
    vao.LinkAttrib(vbo,0, 3, GL_FLOAT, 6*sizeof(GL_FLOAT), (void*)0);

    // link attribute for the colors
    vao.LinkAttrib(vbo,1, 3, GL_FLOAT, 6*sizeof(GL_FLOAT), (void*)(3*sizeof(GL_FLOAT)));

    vao.Unbind();
    iao.Unbind();
    

    while( !glfwWindowShouldClose(window) ){
        // polls for mouse events
        glfwPollEvents(); 

        processInput(window);

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //glUseProgram(shaderProgram);
        shader.Bind();
        shader.SetUniform4f("u_Color", r, 0.2f, 0.9f, 1.0f);
        
        vao.Bind();
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        if( r > 1.0f ){
            increment = -0.05f;
        } else if (r < 0.0f){
            increment = 0.05f;
        }
        r += increment;

        // double buffering for front buffer (currently shown)
        // and back buffer (current being drawn upon)
        glfwSwapBuffers(window);
    }

    vbo.Delete();
    iao.Delete();
    shader.Delete();
    vao.Delete();

    glfwTerminate();

    return  EXIT_SUCCESS;
}
