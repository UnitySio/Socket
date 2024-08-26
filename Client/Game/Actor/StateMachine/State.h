#pragma once

class StateMachine;

class State
{
public:
    State(StateMachine* owner);
    virtual ~State() = default;

protected:
    friend class StateMachine;

    virtual inline void OnEnter() {};
    virtual inline void OnExit() {};
    virtual inline void OnPhysicsTick(float delta_time) {};
    virtual inline void OnTick(float delta_time) {};
    virtual inline void OnPostTick(float delta_time) {};

    StateMachine* owner_;
    
};
