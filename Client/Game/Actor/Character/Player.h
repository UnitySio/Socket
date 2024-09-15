#pragma once
#include "CharacterBase.h"

class Player : public CharacterBase
{
    SHADER_CLASS_HELPER(Player)
    
public:
    Player(const std::wstring& kName);
    virtual ~Player() override = default;

    virtual void BeginPlay() override;
    virtual void Tick(float delta_time) override;

private:
    class Sprite* sprite_;
    
};
