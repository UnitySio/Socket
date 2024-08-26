#pragma once
#include "Actor/StateMachine/State.h"

class PlayerIdleState : public State
{
public:
    PlayerIdleState(StateMachine* owner);
    virtual ~PlayerIdleState() override = default;

protected:
    virtual void OnTick(float delta_time) override;
    virtual void OnEnter() override;
};
