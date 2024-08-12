#pragma once
#include "Actor/Actor.h"

class State;

class StateMachine : public Actor
{
public:
    StateMachine(const std::wstring& kName);
    virtual ~StateMachine() override = default;

    virtual void Tick(float delta_time) override;

    void ChangeState(const std::shared_ptr<State>& new_state);

private:
    std::shared_ptr<State> current_state_;
    
};
