#ifndef GLBUFFER_HPP
# define GLBUFFER_HPP
# include <iostream>
# include <GL/glew.h>
# include <string>

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
		void		SetName(std::string const name);

    private:
        void        Init(void);
		std::string	_name;	
        GLuint      _bufferId;
        GLsizeiptr  _buffSize;
};

#endif
