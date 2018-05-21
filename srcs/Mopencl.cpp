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
	this->global_item_size = 1024;
}

Mopencl::Mopencl(Mopencl const & src)
{
	*this = src;
}

Mopencl::~Mopencl(void)
{
	std::cout << "Mopencl destructor called" << std::endl;
	delete this->kernel;
	std::cout << "Mopencl deleting command queue" << std::endl;
	if (this->command_queue)
		clReleaseCommandQueue(this->command_queue);
	std::cout << "Mopencl deleting context" << std::endl;
	if (this->context)
		clReleaseContext(this->context);
	std::cout << "Mopencl done" << std::endl;
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

bool Mopencl::Init(std::string & kernel_filepath, std::string & entrypoint,
	std::vector<KernelArg*> & args)
{
	cl_int		ret;

	std::cout << "init opencl" << std::endl;
	if (this->errored(clGetPlatformIDs(1, &this->platform_id, NULL)))
		return (false);
	if (this->errored(clGetDeviceIDs(this->platform_id, CL_DEVICE_TYPE_GPU, 1, &this->device_id, NULL)))
		return (false);
	this->context = clCreateContext(NULL, 1, &this->device_id,
		&Mopencl::notify, NULL, &ret);
	if (ret != CL_SUCCESS)
	{
		std::cout << "Error: failed to create context" << std::endl;
		return (false);
	}
	this->command_queue = clCreateCommandQueue(this->context, this->device_id, 0, &ret);
	if (!(this->kernel->load(kernel_filepath)))
		return (false);
	this->program = clCreateProgramWithSource(this->context, 1,
		static_cast<const char **>(static_cast<void*>(&this->kernel->source)),
		&this->kernel->size, &ret);
	if (this->errored(ret))
		return (false);
	if (this->errored(clBuildProgram(this->program, 1, &this->device_id, NULL, NULL, NULL)))
		return (false);
	if (this->errored(this->kernel->build(this->program, entrypoint)))
		return (false);

	// setup arguments here, before clEnqueueNDRangeKernel
	if (this->kernel->setArguments(this->context, args) != CL_SUCCESS)
		return (false);

	if (this->errored(clEnqueueNDRangeKernel(this->command_queue, this->kernel->getId(),
			1, NULL, &this->global_item_size, &this->local_item_size, 0, NULL, NULL)))
		return (false);
	// at this point the kernel is running in case of no errors
	if (!this->errored(ret))
		this->run();
	else
		return (false);
	return (true);
}

void Mopencl::deleteArgs(std::vector<KernelArg*> & args)
{
	std::vector<KernelArg*>::iterator	i;

	for (i = args.begin(); i != args.end(); i++)
		delete *i;
}

void Mopencl::run(void)
{
	std::cout << "kernel payload is running on the graphic card" << std::endl;
	clFlush(this->command_queue);
	clFinish(this->command_queue);
}

bool Mopencl::getBuff(cl_mem buff, size_t size, void *target)
{
	cl_int			ret;

	ret = clEnqueueReadBuffer(this->command_queue, buff, CL_TRUE, 0, size,
		target, 0, NULL, NULL);
	return (ret == CL_SUCCESS);
}