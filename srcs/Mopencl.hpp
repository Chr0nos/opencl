/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mopencl.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snicolet <marvin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 00:43:24 by snicolet          #+#    #+#             */
/*   Updated: 2018/05/08 14:37:53 by snicolet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOPENCL_HPP
# define MOPENCL_HPP
# define CL_USE_DEPRECATED_OPENCL_1_2_APIS
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif
# include <string>
# include "kernel.hpp"

typedef struct			s_error_pair {
	const char			*str;
	cl_int				code;
}						t_error_pair;

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
	(t_error_pair){"invalid value", CL_INVALID_VALUE},
	(t_error_pair){"invalid platform", CL_INVALID_PLATFORM},
	(t_error_pair){NULL, 0}
};

class	Mopencl
{
	public:
							Mopencl(void);
							Mopencl(Mopencl const & src);
							~Mopencl(void);
		Mopencl&			operator=(Mopencl const & src);
		bool				Init(std::string & kernel_filepath, std::string & entrypoint);
		void static			notify(const char *errinfo, const void *private_info,
			size_t cb, void *user_data);

	private:
		bool				errored(cl_int const code);
		cl_context			context;
		cl_command_queue	command_queue;
		cl_platform_id		platform_id;
		cl_program			program;
		Kernel				*kernel;
		cl_device_id		device_id;
		size_t				global_item_size;
		size_t				local_item_size;

	protected:
		void				run(void);
};

#endif
