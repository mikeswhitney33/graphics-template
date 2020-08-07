#include "exceptions.hpp"


Exception::Exception(const std::string & message)
:message(message)
{}

std::string Exception::what() const {
    return message;
}

PipelineException::PipelineException(const std::string & message)
:Exception("PipelineException: " + message)
{}

ShaderException::ShaderException(const std::string & message)
:Exception("ShaderException: " + message)
{}
