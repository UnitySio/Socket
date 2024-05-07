#pragma once

#include "Singleton.h"

class Time : public Singleton<Time>
{
public:
    Time();
    virtual ~Time() override = default;

    static float Init();

    static float Seconds();

private:
    static float frequency_;
    
};