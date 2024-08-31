#pragma once
#include "Actor/StateMachine/State.h"

class PlayerAttack2State : public State
{
public:
    PlayerAttack2State(StateMachine* owner);
    virtual ~PlayerAttack2State() override = default;

protected:
    virtual void OnTick(float delta_time) override;
    virtual void OnEnter() override;
};