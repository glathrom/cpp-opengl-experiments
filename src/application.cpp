#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <c++/8/iostream>


int main(void){

    GLFWwindow* window;

    /* ******************************************************** */
    // creates an opengl window so that glew has something
    // at which to point 
    
    if(!glfwInit())
        return -1;

    window = glfwCreateWindow(640,480,"Hello World", NULL, NULL);
    if(!window){
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    /* ******************************************************** */
    
    if(glewInit() != GLEW_OK)
        std::cout << "Error with glewInit" << std::endl;

    // the positions for the triangle
    float positions[6] = {
        -0.5f, -0.5f,
         0.5f,  0.5f,
         0.5f, -0.5f
    };

    /////////////////////////////////////////////////////////////
    // creates a buffer of data on which opengl can operate
    /////////////////////////////////////////////////////////////
    
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), positions, GL_STATIC_DRAW);


    /////////////////////////////////////////////////////////////
    // creates an attribute array which tells opengl
    // how the buffer created above is supposed to be parsed
    // essentially this is telling opengl how the data is going
    // to be structured - defining a STRUCT in C for example
    /////////////////////////////////////////////////////////////

    // the index is actually the index of the pointer 
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);


    /////////////////////////////////////////////////////////////
    // creates a shader which is basically a source program
    // which must then be compiled and set to the GPU
    // using the struct and the data which are defined above
    /////////////////////////////////////////////////////////////


    while(!glfwWindowShouldClose(window)){

        glClear(GL_COLOR_BUFFER_BIT);

        /*
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f( 0.5f,  0.5f);
        glVertex2f( 0.5f, -0.5f);
        glEnd();
        */

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents(); 
    }

    glfwTerminate();
    
    return 0;
}
