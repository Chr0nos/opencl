#ifndef KERNEL_HPP
# define KERNEL_HPP
# include <string>
# include <fstream>
# include <string>
# include <iostream>

class Kernel
{
    public:
        Kernel(void);
        Kernel(std::string & filepath);
        ~Kernel(void);
        size_t length(void);
        char * getSource(void);
        size_t * GetSize(void);

        char        *source;
        size_t      size;
    private:
        const char  *path;
        bool        load(std::string &filepath);
};

#endif