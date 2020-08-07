#include "shader.hpp"
#include "exceptions.hpp"

Shader::Shader()
:program(glCreateProgram())
{

}

Shader::~Shader()
{
    glDeleteProgram(program);
}
void Shader::addVertexShader(const char * source) const
{
    addShader(GL_VERTEX_SHADER, source);
}

void Shader::addVertexShaderFromFile(const char * filename) const
{
    addShaderFromFile(GL_VERTEX_SHADER, filename);
}
void Shader::addFragmentShader(const char * source) const
{
    addShader(GL_FRAGMENT_SHADER, source);
}
void Shader::addFragmentShaderFromFile(const char * filename) const
{
    addShaderFromFile(GL_FRAGMENT_SHADER, filename);
}

void Shader::addVertexShader(const std::string & source) const
{
    addVertexShader(source.c_str());
}
void Shader::addVertexShaderFromFile(const std::string &filename) const
{
    addVertexShaderFromFile(filename.c_str());
}
void Shader::addFragmentShader(const std::string & source) const
{
    addFragmentShader(source.c_str());
}
void Shader::addFragmentShaderFromFile(const std::string & filename) const
{
    addFragmentShaderFromFile(filename.c_str());
}


void Shader::link() const
{
    glLinkProgram(program);
    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if(!success) {
        glGetProgramInfoLog(program, 512, nullptr, infoLog);
        throw ShaderException("PROGRAM::LINK_ERROR:\n" + std::string(infoLog));
    }
}
void Shader::use() const
{
    glUseProgram(program);
}

void Shader::addShader(unsigned int type, const char * source) const
{
    unsigned int shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        throw ShaderException(shadertype_string(type) + "::COMPILE_ERROR:\n" + std::string(infoLog));
    }
    glAttachShader(program, shader);
    glDeleteShader(shader);
}

void Shader::addShaderFromFile(unsigned int type, const char * filename) const
{
    std::ifstream file(filename);
    if(!file.is_open()) {
        throw ShaderException("unable to open" + std::string(filename));
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    addShader(type, buffer.str().c_str());
}


std::string Shader::shadertype_string(unsigned int type) const
{
    switch(type)
    {
    case GL_VERTEX_SHADER:
        return "VERTEX_SHADER";
    case GL_FRAGMENT_SHADER:
        return "FRAGMENT_SHADER";
    default:
        return "UNSUPPORTED_SHADER";
    }
}

