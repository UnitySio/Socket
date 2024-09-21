#pragma once
#include "Actor/Character/CharacterBase.h"

#include "Actor/StateMachine/State.h"

class Player : public CharacterBase
{
    SHADER_CLASS_HELPER(Player)
    
public:
    Player(const std::wstring& kName);
    virtual ~Player() override = default;

    virtual void BeginPlay() override;
    virtual void Tick(float delta_time) override;
    
    inline State* GetState(int index) const { return states_[index].get(); }

    inline float GetGravity() const { return gravity_; }
    inline float GetJumpVelocity() const { return jump_velocity_; }

    inline void SetMoveSpeed(float move_speed) { move_speed_ = move_speed; }
    inline float GetMoveSpeed() const { return move_speed_; }

    inline void ResetLastPressedJumpTime() { last_pressed_jump_time_ = 0.f; }
    inline float GetLastPressedJumpTime() const { return last_pressed_jump_time_; }

private:
    void HandleTime(float delta_time);
    
    class Sprite* sprite_;

    std::unique_ptr<State> states_[2];

    float gravity_;
    float jump_height_;
    float time_to_jump_apex_;
    float jump_velocity_;
    float move_speed_;
    float last_pressed_jump_time_;
    
};
