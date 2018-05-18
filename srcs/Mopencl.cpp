/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mopencl.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 00:44:40 by snicolet          #+#    #+#             */
/*   Updated: 2018/05/08 14:37:10 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Mopencl.hpp"
#include <iostream>

Mopencl::Mopencl(void)
{
	std::cout << "OpenCL init" << std::endl;
	this->context = 0;
	this->command_queue = 0;
	this->kernel = new Kernel;
	this->platform_id = 0;
	this->device_id = 0;
	this->program = 0;
	this->local_item_size = 1;
	this->global_item_size = 12;
}

Mopencl::Mopencl(Mopencl const & src)
{
	*this = src;
}

Mopencl::~Mopencl(void)
{
	std::cout << "destructor called" << std::endl;
	delete this->kernel;
	std::cout << "deleting command queue" << std::endl;
	clReleaseCommandQueue(this->command_queue);
	std::cout << "deleting context" << std::endl;
	clReleaseContext(this->context);
}

Mopencl& Mopencl::operator=(Mopencl const & src)
{
	if (&src != this)
	{
	}
	return (*this);
}

void Mopencl::notify(const char *errinfo, const void *private_info,
	size_t cb, void *user_data)
{
	(void)private_info;
	(void)user_data;
	(void)cb;
	std::cout << "error: [notify]: " << errinfo << std::endl;
}

bool Mopencl::errored(cl_int const code)
{
	if (code == CL_SUCCESS)
		return (false);
	for (size_t p = 0; g_errors[p].str ; p++)
	{
		if (g_errors[p].code == code)
		{
			std::cout << "error: " << g_errors[p].str << " (" << code << ")" << std::endl;
			return (true);
		}
	}
	std::cout << "error: unknow error (" << code << ")" << std::endl;
	return (true);
}

bool Mopencl::Init(std::string & kernel_filepath)
{
	cl_int		ret;

	std::cout << "init opencl" << std::endl;
	clGetPlatformIDs(1, &this->platform_id, NULL);
	clGetDeviceIDs(this->platform_id, CL_DEVICE_TYPE_GPU, 1, &this->device_id, NULL);
	this->context = clCreateContext(NULL, 1, &this->device_id,
		&Mopencl::notify, NULL, &ret);
	this->command_queue = clCreateCommandQueue(this->context, this->device_id, 0, &ret);
	this->kernel->load(kernel_filepath);
	this->program = clCreateProgramWithSource(this->context, 1,
		static_cast<const char **>(static_cast<void*>(&this->kernel->source)),
		&this->kernel->size, &ret);
	if (this->errored(ret))
		return (false);
	if (this->errored(clBuildProgram(this->program, 1, &this->device_id, NULL, NULL, NULL)))
		return (false);
	ret = this->kernel->build(this->program);
	ret = clEnqueueNDRangeKernel(this->command_queue, this->kernel->getId(), 1, NULL,
		&this->global_item_size, &this->local_item_size, 0, NULL, NULL);
	// at this point the kernel is running in case of no errors
	if (!this->errored(ret))
		this->run();
	else
		return (false);
	return (true);
}

void Mopencl::run(void)
{
	std::cout << "kernel payload is running on the graphic card" << std::endl;
}