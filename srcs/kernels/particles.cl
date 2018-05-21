#define FLAG_GRAVITY_ON (1u << 0)

#pragma pack(push, 1)

struct				s_particle
{
	float3			position;
	float3			velocity;
};

#pragma pack(pop)

struct				s_config
{
	unsigned int	flags;
	float3			gravity_point;
	float			gravity_intensity;
	float3			color_start;
};

void		kernel	render(__global struct s_particle *particles,
	size_t particles_count)
{
	const int					id = get_global_id(0);
	const size_t				total_kernels_count = get_global_size(0);
	const size_t				slize_size = particles_count / total_kernels_count;
	const size_t				offset = id * slize_size;
	__global struct s_particle	*particle;

	printf("[%d] -> (%lu) [%lu] {%lu::%lu} %lu\n",
		id, total_kernels_count, slize_size,
		offset, offset + slize_size, particles_count);

	for (size_t p = 0; p < slize_size ; p++)
	{
		particle = &particles[offset + p];
		particle->position = (float3){1.0f, 42.0f, -1.0f};
		particle->velocity = (float3){1.0f * p, 0.0f, 0.0f};
	}

	printf("[%d] -> finished\n", id);
}
