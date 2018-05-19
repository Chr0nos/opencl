/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 00:47:03 by snicolet          #+#    #+#             */
/*   Updated: 2018/05/08 14:38:00 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#define	PARTICLES_MEM (sizeof(int) * 4) * PARTICLES_COUNT

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

int		main(int ac, char **av)
{
	std::string	filepath = std::string(av[1]);
	std::string kernel_entrypoint = "render";
	Mopencl		cl;

	if (ac < 2)
		return (EXIT_BADARG);
	std::cout << "-------- START OF OPENCL INIT PART ---------" << std::endl;
	cl.Init(filepath, kernel_entrypoint);
	std::cout << "--------- END OF OPENCL INIT PART ---------" << std::endl;

	std::cout << "--------- START OF OPENGL PART ------------" << std::endl;
	std::cout << "making particles mvram buffer" << std::endl;
	// cl::Buffer test = cl.CreateBuffer(PARTICLES_MEM);
	std::cout << "vram buffer done (" << PARTICLES_MEM << ")" << std::endl;
	// passing buffer to the program
	// cl.RunProgram().setArg(0, test);
	// return (run_window(cl));
	return (EXIT_SUCCESS);
}
