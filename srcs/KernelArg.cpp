#include "KernelArg.hpp"

KernelArg::KernelArg(void *ptr, size_t size, cl_mem_flags protection, bool memobj)
{
    this->ptr = ptr;
    this->size = size;
    this->protection = protection;
    this->id = nullptr;
    this->memobj = memobj;
    std::cout << "KernelArg instancied" << std::endl;
}

KernelArg::~KernelArg(void)
{
    if ((this->id) && (this->memobj))
    {
        clReleaseMemObject(this->id);
    }
    std::cout << "KernelArg deleted" << std::endl;
}

cl_int KernelArg::allocate(cl_context context)
{
    cl_int     ret;

    std::cout << "KernelArg allocating " << this->size << std::endl;
    this->id = clCreateBuffer(context, this->protection,
        this->size, nullptr, &ret);
    this->size = sizeof(cl_mem);
    return (ret);
}