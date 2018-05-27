#include "KernelArg.hpp"

KernelArg::KernelArg(void *ptr, size_t size, cl_mem_flags protection)
{
    this->ptr = ptr;
    this->size = size;
    this->protection = protection;
    this->id = nullptr;
    std::cout << "KernelArg instancied" << std::endl;
}

KernelArg::~KernelArg(void)
{
    std::cout << "KernelArg deleted" << std::endl;
}

// this functions has to be overloaded for cl_mem objets
bool KernelArg::send(const cl_context context, const cl_kernel kernel, const cl_uint index)
{
    std::cout << "Regular kernel arg " << index << std::endl;
    (void)context;
    return (clSetKernelArg(kernel, index, this->size, this->ptr) == CL_SUCCESS);
}