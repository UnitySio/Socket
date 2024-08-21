#include "pch.h"
#include "StateMachine.h"

#include "State.h"

StateMachine::StateMachine(const std::wstring& kName) :
    Super(kName)
{
}

void StateMachine::PhysicsTick(float delta_time)
{
    Super::PhysicsTick(delta_time);

    if (current_state_)
    {
        current_state_->OnPhysicsTick(delta_time);
    }
}

void StateMachine::Tick(float delta_time)
{
    Super::Tick(delta_time);

    if (current_state_)
    {
        current_state_->OnTick(delta_time);
    }
}

void StateMachine::PostTick(float delta_time)
{
    Super::PostTick(delta_time);

    if (current_state_)
    {
        current_state_->OnPostTick(delta_time);
    }
}

void StateMachine::ChangeState(const std::shared_ptr<State>& new_state)
{
    if (current_state_)
    {
        current_state_->OnExit();
    }

    current_state_ = new_state;

    if (current_state_)
    {
        current_state_->OnEnter();
    }
}
