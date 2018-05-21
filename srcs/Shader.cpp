#include "Shader.hpp"
#include <fstream>
#include <iostream>

Shader::Shader(void)
{
    this->type = 0;
    this->id = 0;
}

Shader::~Shader(void)
{
    if (this->id)
        glDeleteShader(this->id);
}

bool Shader::BuildFile(char const * filepath, GLuint const type)
{
    std::ifstream       ifs(filepath, std::ifstream::binary);
    char                *shader_code;
    size_t              length;
    bool                ret;

    std::cout << "Shader build source from " << filepath << std::endl;
    ifs.seekg(0, ifs.end);
    length = (size_t)ifs.tellg();
    ifs.seekg(0, ifs.beg);
    shader_code = new char[length];
    if (!shader_code)
        return (false);
    ifs.read(shader_code, (std::streamsize)length);
    ifs.close();
    ret = this->Build(shader_code, length, type);
    delete shader_code;
    std::cout << "Shader build state: " << ((ret) ? "Success" : "Failed") << std::endl;
    return (ret);
}

bool Shader::ShowError(void)
{
    GLint		success;
	int			error_len;
	char		*error;

    std::cout << "Shader checking for compile state" << std::endl;
	glGetShaderiv(this->id, GL_COMPILE_STATUS, &success);
	glGetShaderiv(this->id, GL_INFO_LOG_LENGTH, &error_len);
	if (!error_len)
        return (false);
    std::cout << "Shader error found" << std::endl;
    error = new char[static_cast<size_t>(error_len + 1)];
    if (!error)
        return (true);
	error[error_len] = '\0';
	glGetShaderInfoLog(this->id, error_len, NULL, error);
    std::cout << "opengl error: " << error << std::endl;
    delete error;
    return (true);
}

bool Shader::Build(char * const source, size_t const size, GLuint const type)
{
    GLint       gsize = (GLint)size;

    std::cout << "Shader creation" << std::endl;
	this->id = glCreateShader(type);
    std::cout << "Shader compiling " << size << " bytes" << std::endl;
    glShaderSource(this->id, 1, (const GLchar *const *)(size_t)&source, &gsize);
	glCompileShader(this->id);
	if (this->ShowError())
		return (false);
	return (true);
}