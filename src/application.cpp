#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


static void GLClearError(){
    while(glGetError() != GL_NO_ERROR);
}

static void GLCheckError(){
    while( GLenum error = glGetError() ){
        std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
    }
}



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
    
    glfwSwapInterval(1);
    
    /* ******************************************************** */
    
    if(glewInit() != GLEW_OK)
        std::cout << "Error with glewInit" << std::endl;

    // the positions for the triangle
    float positions[8] = {
        -0.5f, -0.5f,
         0.5f,  0.5f,
         0.5f, -0.5f,
        -0.5f,  0.5f
    };

    unsigned int indices[] = {
        0, 1, 2, 
        0, 3, 1
    };

    /////////////////////////////////////////////////////////////
    // creates a buffer of data on which opengl can operate
    /////////////////////////////////////////////////////////////
    
    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 4*2*sizeof(float), positions, GL_STATIC_DRAW);


    /////////////////////////////////////////////////////////////
    // creates an attribute array which tells opengl
    // how the buffer created above is supposed to be parsed
    // essentially this is telling opengl how the data is going
    // to be structured - defining a STRUCT in C for example
    /////////////////////////////////////////////////////////////

    // the index is actually the index of the pointer 
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), 0);
    
    
    // using an index buffer to render the object 

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(unsigned int), indices, GL_STATIC_DRAW);


    /////////////////////////////////////////////////////////////
    // creates a shader which is basically a source program
    // which must then be compiled and set to the GPU
    // using the struct and the data which are defined above
    /////////////////////////////////////////////////////////////
   
    std::string vertexShader = ReadShader("../res/shaders/basic.vert");
    std::string fragmentShader = ReadShader("../res/shaders/basic.frag");

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    float r = 0.0f;
    float increment = 0.05f;
    int location = glGetUniformLocation(shader, "u_Color");
    glUniform4f(location, r, 0.2f, 0.9f, 1.0f);
    GLCheckError();

    

    while(!glfwWindowShouldClose(window)){

        glClear(GL_COLOR_BUFFER_BIT);

        //glDrawArrays(GL_TRIANGLES, 0, 6);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        GLCheckError();

        if( r > 1.0f ){
            increment = -0.05f;
        } else if (r < 0.0f){
            increment = 0.05f;        
        }

        r += increment;
    
        glUniform4f(location, r, 0.2f, 0.9f, 1.0f);

        glfwSwapBuffers(window);
        
        glfwPollEvents(); 
    }

    glDeleteProgram(shader); 

    glfwTerminate();
    
    return 0;
}
