/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mopencl.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 00:44:40 by snicolet          #+#    #+#             */
/*   Updated: 2018/04/26 01:01:20 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mopencl.hpp"
#include <iostream>

Mopencl::Mopencl(void)
{
	this->_selected_device = 0;
	this->_selected_platform = 0;
	cl::Platform::get(&this->_platforms);
	std::cout << "init ok" << std::endl;
}

Mopencl::Mopencl(Mopencl const & src)
{
	*this = src;
}

Mopencl::~Mopencl(void)
{
	std::cout << "destructor called" << std::endl;
}

Mopencl& Mopencl::operator=(Mopencl const & src)
{
	if (&src != this)
	{
	}
	return (*this);
}

void Mopencl::ListPlatforms()
{
	cl_uint						id;

	if (this->_platforms.empty())
		return ;
	std::cout << "platforms count: " << this->_platforms.size() << std::endl;
	id = 0;
	for (VECTOR_CLASS<cl::Platform>::iterator it = this->_platforms.begin();
		it != this->_platforms.end(); it++)
	{
		cl::Platform		platform(*it);

		std::cout << "id: " << id++ << std::endl;
		std::cout << "name: " << platform.getInfo<CL_PLATFORM_NAME>() << std::endl;
		std::cout << "vendor: " << platform.getInfo<CL_PLATFORM_VENDOR>() << std::endl;
		std::cout << "version: " << platform.getInfo<CL_PLATFORM_VERSION>() << std::endl;
	}
}

bool Mopencl::SelectPlatform(const cl_uint id)
{
	std::cout << "selecting platform: " << id << std::endl;
	if (id > this->_platforms.size())
		return (false);
	this->_selected_platform = id;
	std::cout << "getting devices...";
	this->_platforms[id - 1].getDevices(CL_DEVICE_TYPE_GPU, &this->_devices);
	std::cout << " done." << std::endl;
	return (true);
}

void Mopencl::ListDevices()
{
	if (this->_devices.empty())
		return ;
	for (VECTOR_CLASS<cl::Device>::iterator dev = this->_devices.begin();
		dev != this->_devices.end(); dev++)
	{
		std::cout << "device: " << dev->getInfo<CL_DEVICE_NAME>() << std::endl;
	}
}

bool Mopencl::CreateContext()
{
	cl_int		err;

	this->_context = cl::Context(this->_devices,
		nullptr, // no properties
		nullptr, // no callback
		nullptr, // no callback user pointer
		&err);
	if (err == CL_SUCCESS)
	{
		std::cout << "context ok" << std::endl;
		return (true);
	}
	std::cout << "error while creating context: ";
	if (err == CL_INVALID_PROPERTY)
		std::cout << "invalid property";
	else if (err == CL_INVALID_VALUE)
		std::cout << "invalid value";
	else if (err == CL_INVALID_DEVICE_TYPE)
		std::cout << "invalid device type";
	else if (err == CL_DEVICE_NOT_AVAILABLE)
		std::cout << "device not available";
	else if (err == CL_DEVICE_NOT_FOUND)
		std::cout << "device not found";
	else if (err == CL_OUT_OF_HOST_MEMORY)
		std::cout << "out of memory";
	std::cout << std::endl;
	return (false);
}

void Mopencl::AddSource(const char *kernel, const size_t size)
{
	this->_sources.push_back({kernel, size});
}

bool Mopencl::BuildProgram()
{
	cl::Program		program(this->_context, this->_sources);
	cl::Device		device;

	device = this->_devices[this->_selected_device];
	if (program.build(this->_devices) != CL_SUCCESS)
	{
		std::cout << "error: failed to build program: " <<
			program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(device) << std::endl;
		return (false);
	}
	std::cout << "program build ok" << std::endl;
	return (true);
}