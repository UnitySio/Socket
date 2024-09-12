#pragma once
#include "Actor/Character/CharacterBase.h"

enum class PlayerState
{
    kLocomotion,
    kEnd
};

class PlayerController : public CharacterBase
{
    SHADER_CLASS_HELPER(PlayerController)
    
public:
    PlayerController(const std::wstring& kName);
    virtual ~PlayerController() override = default;

    virtual void BeginPlay() override;
    virtual void EndPlay(EndPlayReason type) override;
    virtual void PhysicsTick(float delta_time) override;
    virtual void Tick(float delta_time) override;

    inline Math::Vector2 GetInputAxis() const { return input_axis_; }
    inline std::shared_ptr<State> GetState(PlayerState state) const { return states_[static_cast<int>(state)]; }
    
private:
    class Sprite* sprite_;

    Math::Vector2 input_axis_;

    float last_pressed_jump_time_;

    int jump_count_;

    std::shared_ptr<State> states_[static_cast<int>(PlayerState::kEnd)];
    
};
