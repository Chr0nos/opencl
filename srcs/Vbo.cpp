#include "Vbo.hpp"

// le vbo contiens les vertex
// Vertex Buffer Object
bool	Vbo::loadRenderTriangles(void)
{
	const GLfloat		triangles[18] = {
		// corner top left
		0.0f, 0.0f, 0.0f,		// top left
		1.0f, 0.0f, 0.0f,		// top right
		0.0f, 1.0f, 0.0f,		// 
		// corner bottom right
		0.0f, 1.0f, 0.0f,		// bottom left
		1.0f, 1.0f, 0.0f,		// top right
		1.0f, 0.0f, 0.0f		// bottom right
	};

	return (this->CreateBuffer(18 * sizeof(GLfloat), (void*)triangles));
}
