#pragma once
#include "Controller2D.h"

class Dummy : public Controller2D
{
    SHADER_CLASS_HELPER(Dummy)
    
public:
    Dummy(const std::wstring& kName);
    virtual ~Dummy() override = default;
    
};
