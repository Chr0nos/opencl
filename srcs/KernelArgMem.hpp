#ifndef KERNEL_ARG_MEM_HPP
# define KERNEL_ARG_MEM_HPP
# define CL_USE_DEPRECATED_OPENCL_1_2_APIS
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif
# include "KernelArg.hpp"
# include <iostream>

class KernelArgMem : public KernelArg {
    public:
        KernelArgMem(void *ptr, size_t size, cl_mem_flags protection);
        ~KernelArgMem(void);
        bool send(const cl_context context, const cl_kernel kernel, const cl_uint index);
};

#endif