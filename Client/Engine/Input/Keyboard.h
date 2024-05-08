#pragma once
#include <functional>
#include <map>

#include "Math/MathTypes.h"

class Keyboard
{
public:
    Keyboard();
    ~Keyboard() = default;

    void BindAxis(MathTypes::uint32 key_code);
    void BindAction(MathTypes::uint32 key_code);

private:
    std::map<MathTypes::uint32, std::function<void(float)>> axis_map_;
    
};
