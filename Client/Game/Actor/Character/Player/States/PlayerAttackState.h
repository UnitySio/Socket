#pragma once
#include "Actor/StateMachine/State.h"

class PlayerAttackState : public State
{
public:
    PlayerAttackState(StateMachine* owner);
    virtual ~PlayerAttackState() override = default;

protected:
    virtual void OnTick(float delta_time) override;
    virtual void OnEnter() override;
};