#define FLAG_GRAVITY_ON (1u << 0)

struct				s_particle
{
	float3			position;
	float3			velocity;
};

struct				s_config
{
	unsigned int	flags;
	float3			gravity_point;
	float			gravity_intensity;
	float3			color_start;
};

void		kernel	render(__global struct s_particle *particles,
	unsigned int particles_count)
{
	const int					id = get_global_id(0);
	const size_t				total_kernels_count = get_global_size(0);
	const size_t				slice_size = particles_count / total_kernels_count;
	size_t						offset;
	__global struct s_particle 	*particle;

	if (slice_size == 0)
		return ;
	offset = id * slice_size;
	printf("[%3d] -> (%lu) [%8lu] {%8lu::%8lu} %lu %u\n",
		id, total_kernels_count, slice_size,
		offset, offset + slice_size, particles_count, sizeof(struct s_particle));

	for (size_t p = 0; p < slice_size; p++)
	{
		particle = &particles[offset + p];
		particle->position = (float3){1.0f, 42.0f, -1.0f};
		particle->velocity = (float3){1.0f * p, 0.0f, 0.0f};
	}

	printf("[%d] -> finished\n", id);
}
