/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 00:47:03 by snicolet          #+#    #+#             */
/*   Updated: 2018/05/19 18:22:39 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include "GlfwWindow.hpp"
#include "Mopencl.hpp"
#include "Vao.hpp"
#include "Vbo.hpp"
#include "Shader.hpp"
#include "kernel.hpp"
#include <string>
#define EXIT_SUCCESS	0
#define EXIT_FAILURE	1
#define EXIT_BADARG		2
#define EXIT_CLPROG		3
#define PARTICLES_COUNT 1000000

# pragma pack(push, 1)

typedef struct			s_particle {
	cl_float3			position;
	cl_float3			velocity;
}						t_particle;

# pragma pack(pop)

#define	PARTICLES_MEM (sizeof(t_particle) * PARTICLES_COUNT)

int		run_window(Mopencl & cl)
{
	GlfwWindow	window("Particle System", 1280, 720);
	Vbo			vbo;

	vbo.SetName(std::string("Dual Triangles Buffer VBO"));
	(void)cl;
	// window display part
	if (!window.Init())
		return (EXIT_FAILURE);

	if (!window.Show())
		return (EXIT_FAILURE);
	
	if (!vbo.loadRenderTriangles())
		return (EXIT_FAILURE);
	window.Render();
	std::cout << "done." << std::endl;
	return (EXIT_SUCCESS);
}

// static void				display_particle(t_particle *particle, size_t amount)
// {
// 	size_t		p;

// 	p = 0;
// 	while (p < amount)
// 	{
// 		std::cout << "[" << p << "] position: " <<
// 			particle->position.x <<
// 			particle->position.y <<
// 			particle->position.z <<
// 			" - velocity: " <<
// 			particle->velocity.x <<
// 			particle->velocity.y <<
// 			particle->velocity.z << std::endl;
// 		particle++;
// 		p++;
// 	}
// }

// main logic:
// Mopencl
//   |
//    \ context
//   \- kernel -> KernelArg
//   \- program

int		main(int ac, char **av)
{
	std::string					filepath = std::string(av[1]);
	std::string					kernel_entrypoint = "render";
	Mopencl						cl;
	std::vector<KernelArg*>		args;
	size_t						particles_count = PARTICLES_COUNT;

	if (ac < 2)
		return (EXIT_BADARG);
	std::cout << "-------- START OF OPENCL INIT PART ---------" << std::endl;
	args.push_back(new KernelArg(nullptr, PARTICLES_MEM, CL_MEM_READ_WRITE, true));
	args.push_back(new KernelArg(&particles_count, sizeof(size_t), CL_MEM_READ_ONLY, false));

	if (!(cl.Init(filepath, kernel_entrypoint, args)))
	{
		Mopencl::deleteArgs(args);
		return (EXIT_FAILURE);
	}
	// t_particle		*test = new t_particle[PARTICLES_COUNT];
	// cl.getBuff(args[0]->id, PARTICLES_MEM, test);
	// // display_particle(test, 20);
	// delete[] test;
	
	std::cout << "--------- END OF OPENCL INIT PART ---------" << std::endl;

	std::cout << "--------- START OF OPENGL PART ------------" << std::endl;
	// return (run_window(cl));
	Mopencl::deleteArgs(args);
	return (EXIT_SUCCESS);
}
