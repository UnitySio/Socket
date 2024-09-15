#pragma once
#include "Actor/StateMachine/State.h"

class PlayerStandingState : public State
{
public:
    PlayerStandingState(Actor* owner, StateMachine* state_machine);
    virtual ~PlayerStandingState() override = default;
    
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void Tick(float delta_time) override;
};
