#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <sstream>
#include <fstream>

class Shader
{
public:
    Shader();
    ~Shader();
    void addVertexShader(const char * source) const;
    void addVertexShaderFromFile(const char * filename) const;
    void addFragmentShader(const char * source) const;
    void addFragmentShaderFromFile(const char * filename) const;

    void addVertexShader(const std::string & source) const;
    void addVertexShaderFromFile(const std::string &filename) const;
    void addFragmentShader(const std::string & source) const;
    void addFragmentShaderFromFile(const std::string & filename) const;

    void link() const;
    void use() const;
protected:

private:
    unsigned int program;
    void addShader(unsigned int type, const char * source) const;
    void addShaderFromFile(unsigned int type, const char * filename) const;
    std::string shadertype_string(unsigned int type) const;
};

#endif // SHADER_HPP