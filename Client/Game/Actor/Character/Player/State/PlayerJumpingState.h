#pragma once
#include "Actor/StateMachine/State.h"
#include "Math/Vector2.h"

class PlayerJumpingState : public State
{
public:
    PlayerJumpingState(Actor* actor, StateMachine* state_machine);
    virtual ~PlayerJumpingState() override = default;
    
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void PhysicsTick(float delta_time) override;
    virtual void Tick(float delta_time) override;
    virtual void PostTick(float delta_time) override;

private:
    class Player* player_;

    class SpriteRendererComponent* sprite_renderer_;
    class AnimatorComponent* animator_;
    class Controller2DComponent* controller_;

    int input_x_;
    int jump_count_;

    Math::Vector2 velocity_;
    
};
