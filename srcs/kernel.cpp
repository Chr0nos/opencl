#include "kernel.hpp"

Kernel::Kernel(void)
{
    this->path = nullptr;
    this->source = nullptr;
    this->size = 0;
    this->id = 0;
    std::cout << "Kernel started" << std::endl;
}

Kernel::~Kernel(void)
{
    if (this->source)
        delete this->source;
    std::cout << "Kernel destroyed (" << this->path << ")" << std::endl;
    clReleaseKernel(this->id);
}

size_t Kernel::length(void)
{
    return (this->size);
}

bool Kernel::load(std::string & filepath)
{
	std::ifstream		ifs(filepath, std::ifstream::binary);
	size_t				length;

    this->path = filepath.c_str();
	std::cout << "kernel read start" << std::endl;
	this->size = 0;
	ifs.seekg(0, ifs.end);
	length = ifs.tellg();
	std::cout << "kernel file: " << filepath << std::endl;
	std::cout << "kernel size: " << length << std::endl;
	ifs.seekg(0, ifs.beg);
    if (this->source)
        delete this->source;
	this->source = new char[length];
	if (!this->source)
		return (false);
	ifs.read(this->source, length);
	ifs.close();
	std::cout << "kernel read ok" << std::endl;
	this->size = length;
    this->id = 0;
    return (true);
}

char *Kernel::getSource(void)
{
    return (this->source);
}

cl_int Kernel::build(cl_program program, std::string & entrypoint)
{
    cl_int      ret;

    this->entrypoint = entrypoint;
    std::cout << "Kernel build (" << this->path << ")" << std::endl;
    this->id = clCreateKernel(program, this->entrypoint.c_str(), &ret);
    return (ret);
}

cl_kernel Kernel::getId(void)
{
    return (this->id);
}

cl_int Kernel::setArguments(cl_context context, std::vector<KernelArg*> & args)
{
    int                                 index;
    std::vector<KernelArg*>::iterator i;

    index = 0;
    for (i = args.begin(); i != args.end(); i++)
    {
        std::cout << "Kernel loading argument: " << index << std::endl;
        if (!(*i)->allocate(context))
        {
            std::cout << "Kernel error: failed to allocate " << (*i)->size <<
                " bytes of memory on device" << std::endl;
            return (CL_MEM_OBJECT_ALLOCATION_FAILURE);
        }
        if (clSetKernelArg(this->id, index++, (*i)->size, (*i)->hostptr) != CL_SUCCESS)
        {
            std::cout << "Kernel argument " << index << " failed" << std::endl;
            return (CL_INVALID_ARG_VALUE);
        }
    }
    std::cout << "Kernel: " << index << " argument(s) successfully set" << std::endl;
    return (CL_SUCCESS);
}