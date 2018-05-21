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
          KernelArg(void *ptr, size_t size, cl_mem_flags protection, bool memobj);
        ~KernelArg(void);
        cl_int allocate(cl_context context);

        void            *ptr;
        cl_mem_flags    protection;
        size_t          size;
        cl_mem          id;
        bool            memobj;
};

#endif