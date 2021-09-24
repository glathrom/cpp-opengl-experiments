#include "shader.h"



std::string get_file_contents(const char * fileName){
    std::ifstream in(fileName, std::ifstream::binary);

    if( in ){
        std::string contents;

        // sets a marker at the end of the file
        in.seekg(0, in.end);

        // tellg returns how many bytes it is to the maker
        // and resizes the string to meet that number of
        // character
        contents.resize(in.tellg());

        // set the file marker back to the beginning of the file
        in.seekg(0, in.beg);

        // now read that number of bytes
        in.read(&contents[0], contents.size());

        // close the file
        in.close();

        return contents;
    }

    // throw an exception if the file cannot be opend
    throw(errno);
};


Shader::Shader(const char* vertexFile, const char* fragmentFile){
    
    std::string vcodeString = get_file_contents(vertexFile);
    std::string fcodeString = get_file_contents(fragmentFile);

    const char* vcode = vcodeString.c_str();
    const char* fcode = fcodeString.c_str();

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vcode, NULL);
    glCompileShader(vertexShader);
    
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fcode, NULL);
    glCompileShader(fragmentShader);
   
    ID = glCreateProgram();
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    glLinkProgram(ID); 

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader(){
    std::cout << "shader destructor ran" << std::endl;
}

void Shader::Activate(){
    glUseProgram(ID);
}

void Shader::Delete(){
    glDeleteProgram(ID);
}
