#include "KernelArg.hpp"

KernelArg::KernelArg(void *hostptr, size_t size, cl_mem_flags protection)
{
    this->hostptr = hostptr;
    this->size = size;
    this->protection = protection;
    this->id = nullptr;
    std::cout << "KernelArg instancied" << std::endl;
}

KernelArg::~KernelArg(void)
{
    if (this->id)
    {
        clReleaseMemObject(this->id);
    }
    std::cout << "KernelArg deleted" << std::endl;
}

cl_int KernelArg::allocate(cl_context context)
{
    cl_int     ret;

    this->id = clCreateBuffer(context, this->protection,
        this->size, this->hostptr, &ret);
    return (ret);
}