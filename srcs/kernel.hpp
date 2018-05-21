#ifndef KERNEL_HPP
# define KERNEL_HPP
# define CL_USE_DEPRECATED_OPENCL_1_2_APIS
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif
# include <string>
# include <fstream>
# include <string>
# include <iostream>
# include <vector>
# include "KernelArg.hpp"

class Kernel
{
    public:
                    Kernel(void);
                   ~Kernel(void);
        size_t      length(void);
        char        *getSource(void);
        bool        load(std::string &filepath);
        cl_int      build(cl_program program, std::string & entrypoint);
        cl_kernel   getId(void);
        cl_int      setArguments(cl_context context, std::vector<KernelArg*> & args);

        char        *source;
        std::string entrypoint;
        size_t      size;


    private:
        const char  *path;
        cl_kernel   id;
};

#endif