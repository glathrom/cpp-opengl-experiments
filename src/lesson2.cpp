#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLEW_STATIC

const char* APP_TITLE = "Introduction to OpenGL - Hello Window 2";
const int WindowWidth = 800;
const int WindowHeight = 600;

void processInput(GLFWwindow *window){
    if( glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

const char* vertexShaderSource = "#version 330 core\n"
"layout (location=0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.2f, 1.0f);\n"
"}\n\0";


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
    
    // shader information ********************************************* 

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    // shader information ********************************************* 
    
    
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
    // the vertex buffer object and the index array
    // arra buffers
    unsigned int VAO, VBO, IAO;
    
    
    // generate the vertex array buffer
    glGenVertexArrays(1, &VAO);
    
    // generate the vertex buffer object
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IAO);

    glBindVertexArray(VAO);
    
    // bind the buffer and describe its type
    // map the data into the buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IAO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindVertexArray(0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    while( !glfwWindowShouldClose(window) ){
        // polls for mouse events
        glfwPollEvents(); 

        processInput(window);

        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        // double buffering for front buffer (currently shown)
        // and back buffer (current being drawn upon)
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwTerminate();

    return  EXIT_SUCCESS;
}
