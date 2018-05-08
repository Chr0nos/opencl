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
# ifdef __APPLE__
#  include "cl.hpp"
# else
#  include <CL/cl.hpp>
# endif

class	Mopencl
{
	public:
							Mopencl(void);
							Mopencl(Mopencl const & src);
							~Mopencl(void);
		Mopencl&			operator=(Mopencl const & src);
		void				ListDevices(void);
		void				ListPlatforms(void);
		bool				SelectPlatform(const cl_uint id);
		bool				CreateContext(void);
		void				AddSource(const char *kernel, const size_t size);
		bool				BuildProgram(void);
		cl::Buffer			CreateBuffer(size_t const size);
		cl::Kernel			RunProgram(void);
		cl::Kernel			RunProgram(cl::Program & program);
		bool				InitQueue(void);

	private:
		VECTOR_CLASS<cl::Platform>		_platforms;
		VECTOR_CLASS<cl::Device>		_devices;
		cl_uint							_selected_platform;
		cl_uint							_selected_device;
		cl::Context						_context;
		cl::Program::Sources			_sources;
		cl::CommandQueue				_queue;
		cl::Program						_program;
};

#endif
