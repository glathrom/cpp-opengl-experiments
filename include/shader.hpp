#ifndef SHADER_CLASS_H
#define SHADER_CLASS_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>
#include <GL/glew.h>

class Shader{
    private:
        std::string m_vertexFilePath;
        std::string m_fragmentFilePath;
        // caching for uniforms
    
    public:
        GLuint ID;
        Shader(const char*, const char*);
        ~Shader();

        void Bind();
        void Unbind();
        void Delete();
        void SetUniform4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);

    private:
        std::string ReadShader(const char *);
        GLuint CompileShader(GLuint type, const std::string& source);
        GLuint GetUniformLocation(const std::string& name);

};



#endif
