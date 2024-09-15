#pragma once
#include "CharacterBase.h"
#include "State/PlayerStandingState.h"

class Player : public CharacterBase
{
    SHADER_CLASS_HELPER(Player)
    
public:
    Player(const std::wstring& kName);
    virtual ~Player() override = default;

    virtual void BeginPlay() override;

private:
    class Sprite* sprite_;

    std::unique_ptr<PlayerStandingState> standing_state_;
    
};
