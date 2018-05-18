#include "kernel.hpp"

Kernel::Kernel(void)
{
    this->path = nullptr;
    this->source = nullptr;
    this->size = 0;
}

Kernel::Kernel(std::string & filepath)
{
    this->path = filepath.c_str();
    this->source = nullptr;
    this->size = 0;
    this->load(filepath);
}

Kernel::~Kernel(void)
{
    std::cout << "Kernel destroyed (" << this->path << ")" << std::endl;
}

size_t Kernel::length(void)
{
    return (this->size);
}

bool Kernel::load(std::string & filepath)
{
	std::ifstream		ifs(filepath, std::ifstream::binary);
	size_t				length;

	std::cout << "kernel read start" << std::endl;
	this->size = 0;
	ifs.seekg(0, ifs.end);
	length = ifs.tellg();
	std::cout << "kernel file: " << filepath << std::endl;
	std::cout << "kernel size: " << length << std::endl;
	ifs.seekg(0, ifs.beg);
	this->source = new char[length];
	if (!this->source)
		return (false);
	ifs.read(this->source, length);
	ifs.close();
	std::cout << "kernel read ok" << std::endl;
	this->size = length;
    return (true);
}