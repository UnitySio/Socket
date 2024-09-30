#pragma once
#include "Singleton.h"

class InputSystem : public Singleton<InputSystem>
{
public:
    InputSystem();
    virtual ~InputSystem() override = default;
    
};
