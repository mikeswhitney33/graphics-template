#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <string>

class Exception
{
public:
    Exception(const std::string & message);
    std::string what() const;
private:
    std::string message;
};

class PipelineException : public Exception
{
public:
    PipelineException(const std::string & message);
};

class ShaderException : public Exception
{
public:
    ShaderException(const std::string & message);
};

#endif // EXCEPTIONS_HPP