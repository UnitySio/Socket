#pragma once

class StateMachine;

class State
{
public:
    State(StateMachine* kOwner);
    virtual ~State() = default;

protected:
    friend class StateMachine;

    inline virtual void OnEnter() {};
    inline virtual void OnExit() {};
    inline virtual void OnUpdate(float delta_time) {};

    StateMachine* owner_;
    
};
