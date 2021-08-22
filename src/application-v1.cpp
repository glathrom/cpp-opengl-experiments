#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <c++/9/iostream>
#include <c++/9/fstream>
#include <c++/9/string>
#include <c++/9/sstream>

const std::string  ReadShader(const std::string& filepath){

    std::ifstream stream(filepath);

    std::string line;
    std::stringstream ss;

    while( std::getline(stream, line) ){
        ss << line << '\n';
    }

    return ss.str();
}


static unsigned int CompileShader(unsigned int type, const std::string& source ){
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    // Error handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if( result == GL_FALSE ){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
    unsigned int program = glCreateProgram();    
    unsigned int vs = CompileShader( GL_VERTEX_SHADER, vertexShader ); 
    unsigned int fs = CompileShader( GL_FRAGMENT_SHADER, fragmentShader); 

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

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
   
    std::string vertexShader = ReadShader("../res/shaders/basic.vert");
    std::string fragmentShader = ReadShader("../res/shaders/basic.frag");

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);



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
