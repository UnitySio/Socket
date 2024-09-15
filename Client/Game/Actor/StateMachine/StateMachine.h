#pragma once

class StateMachine
{
public:
    StateMachine();
    ~StateMachine() = default;

    void Tick(float delta_time);
    
};
