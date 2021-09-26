#ifndef VAO_CLASS_H
#define VAO_CLASS_H 

#include <GL/glew.h>
#include "vbo.hpp"

class VAO {
    public:
        GLuint ID;
        VAO();
        ~VAO();

        void LinkAttrib(VBO VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
        void Bind();
        void Unbind();
        void Delete();

};

#endif /* ifndef VAO_CLASS_H */
