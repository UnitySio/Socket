#pragma once
#include "Actor/Character/Player/PlayerController.h"
#include "Actor/StateMachine/State.h"

namespace Player
{
    class LocomotionState : public State
    {
    public:
        LocomotionState(StateMachine* owner);
        virtual ~LocomotionState() override = default;

        virtual void OnEnter() override;
        virtual void OnPhysicsTick(float delta_time) override;
        virtual void OnTick(float delta_time) override;

    private:
        PlayerController* player_;
        
        AnimatorComponent* animator_;
        
    };
}
