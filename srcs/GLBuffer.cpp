#include "GLBuffer.hpp"

GLBuffer::GLBuffer(size_t const size, void * const data)
{
    this->Init();
    std::cout << "GLBuffer instancied" << std::endl;
    this->CreateBuffer(size, data);
}

GLBuffer::GLBuffer(void)
{
    std::cout << "GLBuffer instancied" << std::endl;
    this->Init();
}

GLBuffer::~GLBuffer(void)
{
    if (this->_bufferId != 0)
      glDeleteBuffers(1, &this->_bufferId);
    std::cout << "GLBuffer deleted" << std::endl;
}

void GLBuffer::Init(void)
{
    this->_buffSize = 0;
    this->_bufferId = 0;
}

GLBuffer& GLBuffer::operator=(GLBuffer & rhs)
{
    if (&rhs != this)
    {
        this->_bufferId = rhs.GetBufferId();
    }
    return (*this);
}

GLuint GLBuffer::GetBufferId(void)
{
    return (this->_bufferId);
}

bool GLBuffer::CreateBuffer(size_t const size, void * const data)
{
    this->_buffSize = size;
    std::cout << "creating buffer..." << std::endl;
    glGenBuffers(1, &this->_bufferId);
    std::cout << "buffer id: " << this->_bufferId << std::endl;
    glBindBuffer(GL_ARRAY_BUFFER, this->_bufferId);
    glBufferData(GL_ARRAY_BUFFER, this->_buffSize, data, GL_STATIC_DRAW);
    std::cout << "buffer is ready" << std::endl;
    return (true);
}

void GLBuffer::Bind(void)
{
    glBindBuffer(GL_ARRAY_BUFFER, this->_bufferId);
}