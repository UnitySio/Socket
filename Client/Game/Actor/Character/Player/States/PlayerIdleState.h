#pragma once
#include "Actor/StateMachine/State.h"

class PlayerIdleState : public State
{
public:
    PlayerIdleState(StateMachine* owner);
    virtual ~PlayerIdleState() override = default;

protected:
    virtual void OnUpdate(float delta_time) override;
    
};
