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