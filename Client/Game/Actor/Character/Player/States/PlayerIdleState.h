#pragma once
#include "Actor/StateMachine/State.h"

class PlayerIdleState : public State
{
public:
    PlayerIdleState(StateMachine* owner);
    virtual ~PlayerIdleState() override = default;

    virtual void OnEnter() override;
    virtual void OnTick(float delta_time) override;

private:
    class PlayerController* player_;
    
};
