﻿#pragma once
#include "Actor/Actor.h"

class State;

class StateMachine : public Actor
{
    SHADER_CLASS_HELPER(StateMachine)
    
public:
    StateMachine(const std::wstring& kName);
    virtual ~StateMachine() override = default;

    virtual void PhysicsTick(float delta_time) override;
    virtual void Tick(float delta_time) override;
    virtual void PostTick(float delta_time) override;

    void ChangeState(const std::shared_ptr<State>& kNewState);
    
private:
    std::shared_ptr<State> current_state_;
    
};
