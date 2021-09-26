#ifndef IAO_CLASS_H
#define IAO_CLASS_H

#include <GL/glew.h>

class IAO {
    public:
        GLuint ID;
        IAO(GLuint* indices, GLsizeiptr size);
        ~IAO();

        void Bind();
        void Unbind();
        void Delete();
};


#endif
