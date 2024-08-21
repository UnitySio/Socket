#pragma once
#include "Actor/Character/CharacterBase.h"

enum class PlayerStates
{
    kIdle,
    kEnd
};

class PlayerController : public CharacterBase
{
    DECLARE_CLASS(CharacterBase, PlayerController)
    
public:
    PlayerController(const std::wstring& kName);
    virtual ~PlayerController() override = default;

    virtual void BeginPlay() override;
    virtual void EndPlay(EndPlayReason type) override;
    virtual void PhysicsTick(float delta_time) override;
    virtual void Tick(float delta_time) override;

private:
    std::shared_ptr<class Sprite> sprite_;

    class TextBlock* text_block_;
    
};
