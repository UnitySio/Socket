#pragma once

class State;

class StateMachine
{
public:
    StateMachine();
    ~StateMachine() = default;

    void PhysicsTick(float delta_time);
    void Tick(float delta_time);
    void PostTick(float delta_time);
    void ChangeState(State* new_state);

private:
    State* current_state_;
    
};
