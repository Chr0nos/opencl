#ifndef VBO_HPP
# define VBO_HPP
# include <iostream>
# include "GLBuffer.hpp"

class Vbo : public GLBuffer
{
	public:
		bool	loadRenderTriangles(void);
};

#endif
