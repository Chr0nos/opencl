/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 00:47:03 by snicolet          #+#    #+#             */
/*   Updated: 2018/05/05 16:05:30 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GlfwWindow.hpp"
#include "Mopencl.hpp"
#include "Vao.hpp"
#include "Vbo.hpp"
#include "Shader.hpp"
#include <fstream>
#include <string>
#include <iostream>
#define EXIT_SUCCESS	0
#define EXIT_FAILURE	1
#define EXIT_BADARG		2
#define EXIT_CLPROG		3
#define PARTICLES_COUNT 1000000
#define	PARTICLES_MEM (sizeof(int) * 4) * PARTICLES_COUNT

char		*loadkernel(std::string const filepath, size_t *size)
{
	std::ifstream		ifs(filepath, std::ifstream::binary);
	char				*kernel;
	size_t				length;

	std::cout << "kernel read start" << std::endl;
	*size = 0;
	ifs.seekg(0, ifs.end);
	length = ifs.tellg();
	std::cout << "kernel file: " << filepath << std::endl;
	std::cout << "kernel size: " << length << std::endl;
	ifs.seekg(0, ifs.beg);
	kernel = new char[length];
	if (!kernel)
		return (nullptr);
	ifs.read(kernel, length);
	ifs.close();
	std::cout << "kernel read ok" << std::endl;
	*size = length;
	return (kernel);
}

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
	size_t		kernel_size;
	char		*kernel;
	Mopencl		cl;


	if (ac < 2)
		return (EXIT_BADARG);
	kernel = loadkernel(av[1], &kernel_size);
	if (!kernel)
		return (EXIT_FAILURE);
	cl.ListPlatforms();
	cl.SelectPlatform(1);
	cl.ListDevices();
	if (!cl.CreateContext())
		return (EXIT_FAILURE);
	cl.AddSource(kernel, kernel_size);
	if (!cl.BuildProgram())
		return (EXIT_CLPROG);
	// not needed anymore.
	delete kernel;
	std::cout << "making particles mvram buffer" << std::endl;
	cl::Buffer test = cl.CreateBuffer(PARTICLES_MEM);
	std::cout << "vram buffer done (" << PARTICLES_MEM << ")" << std::endl;
	// passing buffer to the program
	cl.RunProgram().setArg(0, test);
	return (run_window(cl));
}
