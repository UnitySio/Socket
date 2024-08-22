#pragma once
#include "Actor/Actor.h"

class State;

class StateMachine : public Actor
{
    DECLARE_SHARED_CLASS(StateMachine, Actor)
    
public:
    StateMachine(const std::wstring& kName);
    virtual ~StateMachine() override = default;

    virtual void PhysicsTick(float delta_time) override;
    virtual void Tick(float delta_time) override;
    virtual void PostTick(float delta_time) override;

    void ChangeState(const std::shared_ptr<State>& new_state);

private:
    std::shared_ptr<State> current_state_;
    
};
