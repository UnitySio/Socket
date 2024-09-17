#include "pch.h"
#include "StateMachine.h"

#include "State.h"

StateMachine::StateMachine() :
    current_state_(nullptr)
{
}

void StateMachine::PhysicsTick(float delta_time)
{
    if (current_state_)
    {
        current_state_->PhysicsTick(delta_time);
    }
}

void StateMachine::Tick(float delta_time)
{
    if (current_state_)
    {
        current_state_->Tick(delta_time);
    }
}

void StateMachine::PostTick(float delta_time)
{
    if (current_state_)
    {
        current_state_->PostTick(delta_time);
    }
}

void StateMachine::ChangeState(State* new_state)
{
    if (current_state_)
    {
        current_state_->Exit();
    }

    current_state_ = new_state;
    current_state_->Enter();
}
