#pragma once
#include "Actor/Character/CharacterBase.h"

class PlayerController : public CharacterBase
{
public:
    PlayerController(const std::wstring& kName);
    virtual ~PlayerController() override = default;

    virtual void PhysicsTick(float delta_time) override;
    virtual void Tick(float delta_time) override;
    virtual void Render(float alpha) override;

private:
    class InputComponent* input_;
    
    SHARED_PTR<class Sprite> sprite_;
    SHARED_PTR<class Shape> shape_;
    
};
