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
    inline float GetWalkSpeed() const { return walk_speed_; }
    inline float GetRunSpeed() const { return run_speed_; }
    
    inline void SetLastPressedJumpTime(float time) { last_pressed_jump_time_ = time; }
    inline float GetLastPressedJumpTime() const { return last_pressed_jump_time_; }

    inline int GetInputX() const { return input_x_; }

private:
    class Sprite* sprite_;

    std::unique_ptr<State> states_[2];

    float gravity_;
    float jump_height_;
    float time_to_jump_apex_;
    float jump_velocity_;
    float walk_speed_;
    float run_speed_;
    float last_pressed_jump_time_;

    int input_x_;
    
};
