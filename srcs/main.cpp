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

#include "Mopencl.hpp"
#include <fstream>
#include <string>
#include <iostream>
#define EXIT_SUCCESS 0

char		*loadkernel(std::string const filepath, size_t *size)
{
	std::ifstream		ifs(filepath, std::ifstream::binary);
	char				*kernel;
	size_t				length;

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
	return (EXIT_SUCCESS);
}
