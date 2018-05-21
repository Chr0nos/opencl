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
          KernelArg(void *hostptr, size_t size, cl_int protection);
        ~KernelArg(void);
        cl_int allocate(cl_context context);

        cl_mem          id;
        cl_mem_flags    protection;
        void            *hostptr;
        size_t          size;
};

#endif