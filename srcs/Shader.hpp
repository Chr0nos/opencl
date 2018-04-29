#ifndef SHADER_HPP
# define SHADER_HPP
# include <GL/glew.h>
# include <string>

class Shader
{
    public:
                    Shader(void);
                    ~Shader(void);
        bool        BuildFile(char const * filepath, GLuint const type);
        bool        Build(char * const source, size_t const size, GLuint const type);
        GLuint      id;
        GLuint      type;
        std::string code;

    private:
        bool        ShowError();
};

#endif