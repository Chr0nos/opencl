/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 00:47:03 by snicolet          #+#    #+#             */
/*   Updated: 2018/04/26 00:50:46 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GlfwWindow.hpp"
#include "Mopencl.hpp"
#include "Vao.hpp"
#include "Vbo.hpp"
#include <fstream>
#include <string>
#include <iostream>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
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
	Vao			vao;

	(void)cl;
	(void)vbo;
	(void)vao;
	// window display part
	if (!window.Init())
		return (EXIT_FAILURE);
	// vbo.CreateBuffer(10, (void * const)"hello world");
//	vao.CreateBuffer(10, (void * const)"hello world", vbo);
	window.Show();
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
		return (2);
	kernel = loadkernel(av[1], &kernel_size);
	if (!kernel)
		return (1);
	cl.ListPlatforms();
	cl.SelectPlatform(1);
	cl.ListDevices();
	cl.CreateContext();
	cl.AddSource(kernel, kernel_size);
	cl.BuildProgram();

	std::cout << "making particles mvram buffer" << std::endl;
	cl::Buffer test = cl.CreateBuffer(PARTICLES_MEM);
	std::cout << "vram buffer done (" << PARTICLES_MEM << ")" << std::endl;
	// passing buffer to the program
	cl.RunProgram().setArg(0, test);
	return (run_window(cl));
}
