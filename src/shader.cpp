#include "shader.hpp"




Shader::Shader(const char* vertexFile, const char* fragmentFile){
    ID = glCreateProgram();

    m_vertexFilePath = vertexFile;
    m_fragmentFilePath = fragmentFile;
    
    std::string vcodeString = ReadShader(vertexFile);
    std::string fcodeString = ReadShader(fragmentFile);

    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vcodeString);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fcodeString);
    
    glAttachShader(ID, vertexShader);
    glAttachShader(ID, fragmentShader);

    glLinkProgram(ID); 
    //glValidateProgram(ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader(){
    std::cout << "shader destructor ran" << std::endl;
}

std::string Shader::ReadShader(const char * fileName){
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


GLuint Shader::CompileShader(GLuint type, const std::string& source){
    const char* src = source.c_str();

    GLuint id = glCreateShader(type);
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    // Error handling
    GLint result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if( result == GL_FALSE ){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char *) alloca(length*sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}


void Shader::Bind(){
    glUseProgram(ID);
}

void Shader::Unbind(){
    glUseProgram(0);
}

void Shader::Delete(){
    glDeleteProgram(ID);
}

void Shader::SetUniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3){
    GLuint id = glGetUniformLocation(ID, name.c_str());
    glUniform4f(id, v0, v1, v2, v3);
}

GLuint Shader::GetUniformLocation(const std::string& name){
    return glGetUniformLocation(ID, name.c_str());
}
