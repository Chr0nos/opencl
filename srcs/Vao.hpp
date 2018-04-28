#ifndef VAO_HPP
# define VAO_HPP
# include "GLBuffer.hpp"

class Vao : public GLBuffer
{
    public:
       bool         CreateBuffer(size_t const size, void * const, GLenum target, Vbo * vbo);

};

#endif