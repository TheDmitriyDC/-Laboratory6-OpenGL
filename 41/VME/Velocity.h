#pragma once
#include "Buffer.h"

#include <string>

class Velocity : public Buffer
{
public:
    void Initialize() override;
    void Bind() override;
};