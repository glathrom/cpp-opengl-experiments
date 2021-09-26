#include "iao.hpp"
#include <iostream>



IAO::IAO(GLuint* indices, GLsizeiptr size){
    glGenBuffers(1, &ID);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

IAO::~IAO(){
    std::cout << "IAO desctructor called" << std::endl;
}


void IAO::Bind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void IAO::Unbind(){
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IAO::Delete(){
    glDeleteBuffers(1, &ID);
}
