#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLEW_STATIC

const char* APP_TITLE = "Introduction to OpenGL - Hello Window 1";
const int WindowWidth = 800;
const int WindowHeight = 600;

void processInput(GLFWwindow *window){
    if( glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

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

    glewExperimental = GL_TRUE;
    if( glewInit() != GLEW_OK ){
        std::cerr << "GLEW initialization failed" << std::endl;
        return EXIT_FAILURE;
    }

    while( !glfwWindowShouldClose(window) ){
        // polls for mouse events
        glfwPollEvents(); 

        processInput(window);

        glClearColor(0.23f, 0.38f, 0.47f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // double buffering for front buffer (currently shown)
        // and back buffer (current being drawn upon)
        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return  EXIT_SUCCESS;
}
