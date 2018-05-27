#include "KernelArgMem.hpp"

KernelArgMem::KernelArgMem(void *ptr, size_t size, cl_mem_flags protection)
    : KernelArg(ptr, size, protection)
{
    // KernelArg::KernelArg(ptr, size, protection);
}

KernelArgMem::~KernelArgMem(void)
{
    std::cout << "KernelArgMem deleted" << std::endl;
    if (this->id)
      clReleaseMemObject(this->id);
}

bool KernelArgMem::send(const cl_context context, const cl_kernel kernel, const cl_uint index)
{
    cl_int          ret;

    std::cout << "KernelArgMem allocating " << this->size << std::endl;
    this->id = clCreateBuffer(context, this->protection, this->size, nullptr, &ret);
    if (ret != CL_SUCCESS)
        return (false);
    this->size = sizeof(cl_mem);
    std::cout << "KernelArgMem setting argument" << std::endl;
    return (clSetKernelArg(kernel, index, this->size, &this->id) == CL_SUCCESS);
}