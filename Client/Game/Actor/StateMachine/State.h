#pragma once

class Actor;
class StateMachine;

class State
{
public:
    State(Actor* owner, StateMachine* state_machine);
    virtual ~State() = default;

    virtual void Enter() = 0;
    virtual void Exit() = 0;
    virtual void Tick(float delta_time) = 0;

protected:
    Actor* owner_;
    StateMachine* state_machine_;
    
};
