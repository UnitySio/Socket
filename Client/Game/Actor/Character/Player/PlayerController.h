#pragma once
#include "Actor/Character/CharacterBase.h"
#include "States/PlayerIdleState.h"
#include "States/PlayerMoveState.h"
#include "States/PlayerAttackState.h"
#include "States/PlayerAttack2State.h"

enum class PlayerStates
{
    kIdle,
    kEnd
};

class PlayerController : public CharacterBase
{
    SHADER_CLASS_HELPER(PlayerController)
    
public:
    PlayerController(const std::wstring& kName);
    virtual ~PlayerController() override = default;

    virtual void Tick(float delta_time) override;

    virtual void BeginPlay() override;
    virtual void EndPlay(EndPlayReason type) override;

    std::shared_ptr<PlayerIdleState> idle_;
    std::shared_ptr<PlayerMoveState> move_;
    std::shared_ptr<PlayerAttackState> attack1_;
    std::shared_ptr<PlayerAttack2State> attack2_;
    
private:
    class Sprite* sprite_;

    class TextBlock* text_block_;
    
    bool is_hit_;
    
};
