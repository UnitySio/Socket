#pragma once
#include "Actor/Character/CharacterBase.h"

class PlayerController : public CharacterBase
{
public:
    PlayerController(const std::wstring& kName);
    virtual ~PlayerController() override = default;

    virtual void BeginPlay() override;
    virtual void PhysicsTick(float delta_time) override;
    virtual void Tick(float delta_time) override;

private:
    void OnFire();
    
    class InputComponent* input_;
    
    std::shared_ptr<class Sprite> sprite_;

    class TextBlock* text_block_;
    
};
