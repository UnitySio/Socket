#pragma once
#include "Actor/StateMachine/State.h"

class PlayerWalkState : public State
{
public:
    PlayerWalkState(StateMachine* owner);
    virtual ~PlayerWalkState() override = default;

    virtual void OnEnter() override;
    virtual void OnPhysicsTick(float delta_time) override;
    virtual void OnTick(float delta_time) override;

private:
    class PlayerController* player_;
    
};
