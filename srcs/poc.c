/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 15:23:26 by snicolet          #+#    #+#             */
/*   Updated: 2018/05/08 19:33:55 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#ifdef __APPLE__
# include <OpenCL/opencl.h>
#else
# include <CL/cl.h>
#endif

typedef struct			s_poc 
{
	cl_uint				ret_num_devices;
	cl_uint				ret_num_platforms;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_platform_id		platform_id;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				a_mem_obj;
	void				*retbuff;
	char				*filepath;
	char				*source;
	size_t				source_size;
	size_t				size;
	cl_device_id		device_id;
}						t_poc;

static int				run(t_poc *poc)
{
	cl_int				ret;

	poc->source = ft_readfile(poc->filepath, &poc->source_size);
	if (!poc->source)
		return (EXIT_FAILURE);
	poc->a_mem_obj = clCreateBuffer(poc->context, CL_MEM_READ_WRITE,
		   	poc->size, NULL, &ret);

	poc->program = clCreateProgramWithSource(poc->context, 1,
			(const char **)(size_t)&poc->source,
			(const size_t *)&poc->source_size, &ret);
	ret = clBuildProgram(poc->program, 1, &poc->device_id, NULL, NULL, NULL);
	if (ret == CL_SUCCESS)
	{
		ft_printf("%s", "program build success\n");
		poc->kernel= clCreateKernel(poc->program, "render", &ret);
		ret = clSetKernelArg(poc->kernel, 0, sizeof(cl_mem), (void *)&poc->a_mem_obj);

//		poc->retbuff = malloc(poc->size);
//		retbuff = clEnqueueReadBuffer(poc->command_queue, poc->a_mem_obj,
//				CL_TRUE, 0, poc->retbuff, poc->size, 0, NULL, NULL);
		clReleaseKernel(poc->kernel);
		clReleaseProgram(poc->program);
	}
	else
		ft_dprintf(STDERR_FILENO, "%s", "error: failed to build program.\n");
	free(poc->source);
	clReleaseMemObject(poc->a_mem_obj);
	return (EXIT_SUCCESS);
}

int						main(int ac, char **av)
{
	cl_int				ret;
	t_poc				poc;
	
	if (ac < 2)
		return (EXIT_FAILURE);
	ft_bzero(&poc, sizeof(poc));
	ret	= clGetPlatformIDs(1, &poc.platform_id, &poc.ret_num_platforms);
	ret = clGetDeviceIDs(poc.platform_id, CL_DEVICE_TYPE_ALL, 1, 
			            &poc.device_id, &poc.ret_num_devices);
	poc.context = clCreateContext(NULL, 1, &poc.device_id, NULL, NULL, &ret);
	poc.command_queue = clCreateCommandQueue(poc.context, poc.device_id, 0, &ret);
	poc.size = 1024 * 768 * sizeof(unsigned int);
	poc.filepath = av[1];
	run(&poc);
	ret = clFlush(poc.command_queue);
	ret = clFinish(poc.command_queue);
	clReleaseCommandQueue(poc.command_queue);
	clReleaseContext(poc.context);
	ft_printf("%p\n", poc.retbuff);
	return (EXIT_SUCCESS);
}
