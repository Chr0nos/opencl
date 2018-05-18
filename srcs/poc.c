/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   poc.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 15:23:26 by snicolet          #+#    #+#             */
/*   Updated: 2018/05/12 12:20:02 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#ifdef __APPLE__
# include <OpenCL/opencl.h>
#else
# include <CL/cl.h>
#endif
#include <stdarg.h>

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
	size_t				global_item_size;
	size_t				local_item_size;
	cl_device_id		device_id;
}						t_poc;

#pragma pack(push, 1)

typedef struct			s_particle {
	cl_float3			position;
	cl_float3			velocity;
}						t_particle;

typedef struct			s_error_pair {
	const char			*str;
	cl_int				code;
}						t_error_pair;

#pragma pack(pop)

static t_error_pair g_errors[] = {
	(t_error_pair){"success", CL_SUCCESS},
	(t_error_pair){"invalid program executable", CL_INVALID_PROGRAM_EXECUTABLE},
	(t_error_pair){"invalid command queue", CL_INVALID_COMMAND_QUEUE},
	(t_error_pair){"invalid kernel", CL_INVALID_KERNEL},
	(t_error_pair){"invalid context", CL_INVALID_CONTEXT},
	(t_error_pair){"invalid kernel args", CL_INVALID_KERNEL_ARGS},
	(t_error_pair){"invalid work dimention", CL_INVALID_WORK_DIMENSION},
	(t_error_pair){"invalid global work size", CL_INVALID_GLOBAL_WORK_SIZE},
	(t_error_pair){"invalid global offset", CL_INVALID_GLOBAL_OFFSET},
	(t_error_pair){"invalid work group size", CL_INVALID_WORK_GROUP_SIZE},
	(t_error_pair){"invalid work item size", CL_INVALID_WORK_ITEM_SIZE},
	(t_error_pair){"misaligned sub buffer offset", CL_MISALIGNED_SUB_BUFFER_OFFSET},
	(t_error_pair){"invalid image size", CL_INVALID_IMAGE_SIZE},
	// (t_error_pair){"invalid image format", CL_INVALID_IMAGE_FORMAT},
	(t_error_pair){"out of ressources", CL_OUT_OF_RESOURCES},
	(t_error_pair){"mem object allocation failure", CL_MEM_OBJECT_ALLOCATION_FAILURE},
	(t_error_pair){"invalid event wait list", CL_INVALID_EVENT_WAIT_LIST},
	(t_error_pair){"out of host memory", CL_OUT_OF_HOST_MEMORY},
	(t_error_pair){"build program failure",  CL_BUILD_PROGRAM_FAILURE},
	(t_error_pair){NULL, 0}
};

static const char		*opencl_strerr(const cl_int code)
{
	size_t				p;

	p = 0;
	while (g_errors[p].str)
	{
		if (g_errors[p].code == code)
			return (g_errors[p].str);
		p++;
	}
	return ("unknow error");
}

static int				poc_error(const char *msg, const int retcode)
{
	ft_dprintf(STDERR_FILENO, "%s%s\n", "error: ", msg);
	return (retcode);
}

static int				is_zeroed(t_buffer buffer)
{
	size_t	p;

	p = 0;
	while (p < buffer.size)
	{
		if (buffer.data[p] != 0)
			return (0);
		p++;
	}
	return (1);
}

static void				run_build_failure(t_poc *poc, const cl_int code)
{
	(void)poc;
	ft_dprintf(STDERR_FILENO, "%s%s (%d)\n", "error: failed to build program: ",
		opencl_strerr(code), code);
}

static void				display_particle(t_particle *particle, size_t amount)
{
	size_t		p;

	p = 0;
	while (p < amount)
	{
		ft_printf("%s%f %f %f%s%f %f %f]\n",
			"position: [",
			(double)particle->position.x, (double)particle->position.y, (double)particle->position.z,
			"] - velocity: [",
			(double)particle->velocity.x, (double)particle->velocity.y, (double)particle->velocity.z);
		particle++;
		p++;
	}
}

static cl_int			set_kernel_args(cl_kernel kernel, const size_t n, ...)
{
	va_list		ap;
	cl_int		ret;
	size_t		i;
	void		*ptr;
	size_t		size;

	va_start(ap, n);
	i = 0;
	while (i < n)
	{
		ptr = va_arg(ap, void*);
		size = va_arg(ap, size_t);
		ret = clSetKernelArg(kernel, (cl_uint)i, size, ptr);
		if (ret != CL_SUCCESS)
		{
			ft_dprintf(STDERR_FILENO, "%s%s%lu%s\n",
				"error: failed to set kernel argument (", i, "): ",
				opencl_strerr(ret));
			return (ret);
		}
		ft_printf("opencl kernel arg %d: OK", i);
		i++;
	}
	va_end(ap);
	return (CL_SUCCESS);
}

static int				run(t_poc *poc)
{
	cl_int				ret;

	poc->local_item_size = 1;
	poc->global_item_size = 12;
	poc->source = ft_readfile(poc->filepath, &poc->source_size);
	if (!poc->source)
		return (EXIT_FAILURE);
	poc->a_mem_obj = clCreateBuffer(poc->context, CL_MEM_READ_WRITE,
		   	poc->size, NULL, &ret);
	ft_printf("%s%s\n", "buffer state: ", opencl_strerr(ret));
	ft_printf("buffer size: %lu (%lu)\n", poc->size, sizeof(t_particle));
	poc->program = clCreateProgramWithSource(poc->context, 1,
			(const char **)(size_t)&poc->source,
			(const size_t *)&poc->source_size, &ret);
	ft_printf("%s%s\n", "program state: ", opencl_strerr(ret));

	ret = clBuildProgram(poc->program, 1, &poc->device_id, NULL, NULL, NULL);
	if (ret == CL_SUCCESS)
	{
		ft_printf("%s", "program build success\n");
		// create da fucking kernel
		poc->kernel= clCreateKernel(poc->program, "render", &ret);
		// set first argument to the damn kernel (passing the buffer as param)
		ret = set_kernel_args(poc->kernel, 2,
			(void*)&poc->a_mem_obj, sizeof(cl_mem),
			&poc->global_item_size, sizeof(size_t));

		poc->retbuff = ft_memalloc(poc->size);
		ft_printf("%s%s\n", "buffer zeored: ", (is_zeroed((t_buffer){ poc->retbuff, poc->size }) == 1 ? "yes" : "no"));

		// it would be great if sometime i runned the kernel, just saying
		// clGetKernelWorkGroupInfo(poc->kernel, poc->device_id, CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t), &poc->local_item_size, NULL);
		ft_printf("local item size: %lu\n", poc->local_item_size);
		ret = clEnqueueNDRangeKernel(poc->command_queue, poc->kernel, 1, NULL, &poc->global_item_size,
			&poc->local_item_size, 0, NULL, NULL);
		ft_printf("enqueue result: %d -> %s\n", ret, opencl_strerr(ret));

		// retrive the buffer data
		ret = clEnqueueReadBuffer(poc->command_queue, poc->a_mem_obj,
				CL_TRUE, 0, poc->size, poc->retbuff, 0, NULL, NULL);
		// wait for the queue to be complete
		ret = clFlush(poc->command_queue);
		ret = clFinish(poc->command_queue);
		ft_printf("%s%s %d\n", "buffer zeored: ",
			(is_zeroed((t_buffer){ poc->retbuff, poc->size }) == 1 ? "yes" : "no"), ret);

		display_particle((t_particle*)(size_t)poc->retbuff, 10);

		clReleaseKernel(poc->kernel);
		clReleaseProgram(poc->program);
	}
	else
		run_build_failure(poc, ret);
	free(poc->source);
	clReleaseMemObject(poc->a_mem_obj);
	return (EXIT_SUCCESS);
}

static void				notify(const char *errinfo, const void *private_info, size_t cb, void *user_data)
{
	ft_dprintf(STDERR_FILENO, "opencl error: %s", errinfo, private_info, user_data, cb);
}

int						main(int ac, char **av)
{
	cl_int				ret;
	t_poc				poc;
	
	if (ac < 2)
		return (EXIT_FAILURE);
	ft_bzero(&poc, sizeof(poc));
	if (clGetPlatformIDs(1, &poc.platform_id, &poc.ret_num_platforms) != CL_SUCCESS)
		return (poc_error("failed to get platform id", EXIT_FAILURE));
	if (clGetDeviceIDs(poc.platform_id, CL_DEVICE_TYPE_ALL, 1,
			            &poc.device_id, &poc.ret_num_devices) != CL_SUCCESS)
		return (poc_error("failed to get device ids", EXIT_FAILURE));
	poc.context = clCreateContext(NULL, 1, &poc.device_id, &notify, NULL, &ret);
	ft_printf("%s%s\n", "context state: ", opencl_strerr(ret));
	poc.command_queue = clCreateCommandQueue(poc.context, poc.device_id, 0, &ret);
	ft_printf("%s%s\n", "command queue state: ", opencl_strerr(ret));
	poc.size = 1024 * 768 * (sizeof(t_particle));
	poc.filepath = av[1];
	run(&poc);
	clReleaseCommandQueue(poc.command_queue);
	clReleaseContext(poc.context);
	ft_printf("%p\n", poc.retbuff);
	return (EXIT_SUCCESS);
}
