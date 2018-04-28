#ifndef GLBUFFER_HPP
# define GLBUFFER_HPP
# include <iostream>
# include <GL/glew.h>

class GLBuffer
{
    public:
                     GLBuffer(size_t const size, void * const data);
                     GLBuffer(void);
                    ~GLBuffer(void);
        GLBuffer&   operator=(GLBuffer & rhs);
        GLuint      GetBufferId(void);
        bool        CreateBuffer(size_t const size, void * const data);
        void        Bind(void);

    private:
        void        Init(void);

    protected:
        GLuint      _bufferId;
        GLsizeiptr  _buffSize;
};

#endif