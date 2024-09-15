#pragma once

class State
{
public:
    State(class StateMachine* state_machine);
    virtual ~State() = default;

    virtual void Enter() = 0;
    virtual void Exit() = 0;
    virtual void Tick(float delta_time) = 0;
    
};
