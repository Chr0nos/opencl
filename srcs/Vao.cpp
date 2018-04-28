#include "Vao.hpp"

bool Vao::CreateBuffer(size_t const size, void * const, GLenum target, Vbo & vbo)
{
    this->_buffSize = size;
    glGenVertexArrays(1, &this->_bufferId);
    glBindVertexArray(this->_bufferId);
    vbo.Bind();
    glBindVertexArray(0);
    return (true);
}