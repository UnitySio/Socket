#include "pch.h"
#include "StateMachine.h"

#include "State.h"

StateMachine::StateMachine(const std::wstring& kName) :
    Actor(kName)
{
}

void StateMachine::Tick(float delta_time)
{
    Actor::Tick(delta_time);

    if (current_state_)
    {
        current_state_->OnUpdate(delta_time);
    }
}

void StateMachine::ChangeState(const std::shared_ptr<State>& new_state)
{
    if (current_state_)
    {
        current_state_->OnExit();
    }

    current_state_ = new_state;
    current_state_->OnEnter();
}
