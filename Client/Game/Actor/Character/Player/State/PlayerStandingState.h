#pragma once
#include "Actor/StateMachine/State.h"
#include "Math/Vector2.h"

class PlayerStandingState : public State
{
public:
    PlayerStandingState(Actor* actor, StateMachine* state_machine);
    virtual ~PlayerStandingState() override = default;
    
    virtual void Enter() override;
    virtual void Exit() override;
    virtual void PhysicsTick(float delta_time) override;
    virtual void Tick(float delta_time) override;
    virtual void PostTick(float delta_time) override;

private:
    void HandleTime(float delta_time);
    
    class Player* player_;

    class SpriteRendererComponent* sprite_renderer_;
    class AnimatorComponent* animator_;
    class Controller2DComponent* controller_;

    int input_x_;
    
    Math::Vector2 velocity_;

    float last_grounded_time_;
    float coyote_time_;
    float last_double_tap_time_;

    bool is_running_;
};
