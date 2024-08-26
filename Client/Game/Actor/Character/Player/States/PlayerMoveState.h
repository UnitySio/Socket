#pragma once
#include "Actor/StateMachine/State.h"

class PlayerMoveState : public State
{
public:
    PlayerMoveState(StateMachine* owner);
    virtual ~PlayerMoveState() override = default;

protected:
    virtual void OnPhysicsTick(float delta_time) override;
    virtual void OnTick(float delta_time) override;
    virtual void OnEnter() override;
};