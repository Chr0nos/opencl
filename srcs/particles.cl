struct				vec3
{
	float			x;
	float			y;
	float			z;
};

struct				s_particle
{
	struct vec3		position;
	unsigned int	color;
};

void		kernel	render(global char *output)
{
	output[0] = 1;
};
