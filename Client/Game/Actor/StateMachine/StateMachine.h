#pragma once

class State;

class StateMachine
{
public:
    StateMachine();
    ~StateMachine() = default;

    void Tick(float delta_time);
    void ChangeState(State* new_state);

private:
    State* current_state_;
    
};
