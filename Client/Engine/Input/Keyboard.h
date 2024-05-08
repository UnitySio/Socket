#pragma once
#include <functional>
#include <map>

#include "Math/MathTypes.h"

struct Action
{
    bool is_down = false;
    
    std::function<void()> Started;
    std::function<void()> Ongoing;
    std::function<void()> Canceled;
};

class Keyboard
{
public:
    Keyboard();
    ~Keyboard() = default;

    void BindAction(MathTypes::uint32 key, Action action);
    void Tick();

private:
    std::map<MathTypes::uint32, Action> actions_;
    
};
