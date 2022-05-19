#include "Exception.h"

void Utilities::Exceptions::Exception::SHException(unsigned int A, std::string Type)
{
    signed int success;
    char infoLog[1024];
    if (Type != "PROGRAM")
    {
        glGetShaderiv(A, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(A, 1024, NULL, infoLog);
            OutputDebugStringA("Shader compilation encountered error:\n");
            OutputDebugStringA("Type: "); OutputDebugStringA(Type.c_str());
            OutputDebugStringA("\n"); OutputDebugStringA(infoLog);
            OutputDebugStringA("\n");
        }
    }
    else
    {
        glGetProgramiv(A, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(A, 1024, NULL, infoLog);
            OutputDebugStringA("Shader linking encountered error:\n");
            OutputDebugStringA("Type: "); OutputDebugStringA(Type.c_str());
            OutputDebugStringA("\n"); OutputDebugStringA(infoLog);
            OutputDebugStringA("\n");
        }
    }
};