#ifndef KERNEL_ARG_HPP
# define KERNEL_ARG_HPP
# define CL_USE_DEPRECATED_OPENCL_1_2_APIS
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif
# include <iostream>

class KernelArg
{
    public:
          KernelArg(void *ptr, size_t size, cl_mem_flags protection);
        ~KernelArg(void);
        bool send(const cl_context context, const cl_kernel kernel, const cl_uint index);

        void            *ptr;
        cl_mem_flags    protection;
        size_t          size;
        cl_mem          id;
};

#endif