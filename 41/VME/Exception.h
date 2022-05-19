#pragma once
#include "GL-Linker.h"
#include <string>

namespace Utilities
{
    namespace Exceptions
    {
        class Exception
        {
        public:
            /// <summary>
            /// Shader Exception Handler.
            /// </summary>
            /// <param name="Shader"></param>
            /// <param name="Type"></param>
            static void SHException(unsigned int Shader, std::string Type);
        };
    };
};