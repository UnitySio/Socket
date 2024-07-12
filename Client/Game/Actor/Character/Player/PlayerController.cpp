﻿#include "PlayerController.h"

#include "GameInstance.h"
#include "Windows.h"
#include "Actor/Box.h"

#include "Actor/Component/BoxColliderComponent.h"
#include "Actor/Component/RigidBodyComponent.h"
#include "Actor/Component/InputComponent.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Actor/Component/Animator/AnimationClip.h"
#include "Actor/Component/Animator/AnimatorComponent.h"
#include "box2d/b2_mouse_joint.h"
#include "Input/Keyboard.h"
#include "Level/World.h"
#include "Misc/Debug.h"
#include "Physics/HitResult.h"
#include "Physics/Physics.h"
#include "UI/Canvas.h"
#include "UI/TextBlock.h"
#include "Windows/DX/Shape.h"
#include "Windows/DX/Sprite.h"
#include "Logger/Logger.h"

PlayerController::PlayerController(const std::wstring& kName) : CharacterBase(kName)
{
    input_ = CreateComponent<InputComponent>(L"Input");
    input_->RegisterKey(VK_RIGHT);
    input_->RegisterKey(VK_LEFT);
    input_->RegisterKey('C');
    input_->RegisterKey('Z');
    
    sprite_ = std::make_shared<Sprite>();
    CHECK_IF(sprite_->Load(L".\\Game_Data\\spritesheet.png"), L"Failed to load texture");
    
    sprite_->Split(15, 3, Sprite::kCenter);

    sprite_renderer_->SetSprite(sprite_);

    int temp[] = {0, 1, 2, 3, 4, 5};
    std::shared_ptr<AnimationClip> clip = animator_->AddClip(L"Idle", temp, 6);
    clip->SetRepeat(true);
    clip->SetFrameRate(6.f);
    clip->AddEvent([this]()->void {text_block_->SetText(L"Hello World"); }, 1);
    clip->AddEvent(this, &PlayerController::Test, 2);

    animator_->PlayClip(clip);
}

void PlayerController::Test()
{
    Logger log;
    log.AddLog(L"a");
}

void PlayerController::BeginPlay()
{
    CharacterBase::BeginPlay();

    text_block_ = Canvas::Get()->CreateTextBlock();
    //text_block_->SetAnchorType(UIBase::AnchorType::Center);
    text_block_->SetText(L"Hello, World!");
    text_block_->SetAlignment(TextBlock::TextAlignment::Center, TextBlock::ParaAlignment::Center);
    text_block_->SetFontStyle(false, false);
    // text_block_->SetTextColor(Math::Color::Cyan);
    text_block_->SetSize({ 250,50 });
}

void PlayerController::PhysicsTick(float delta_time)
{
    CharacterBase::PhysicsTick(delta_time);

    Keyboard* keyboard = Keyboard::Get();

    const float h = keyboard->IsKeyDown(VK_RIGHT) - keyboard->IsKeyDown(VK_LEFT);
    if (h != 0.f) sprite_renderer_->SetFlipX(h > 0.f);
    
    rigid_body_->SetVelocity({h * 6.f, rigid_body_->GetVelocity().y});
}

void PlayerController::Tick(float delta_time)
{
    CharacterBase::Tick(delta_time);
    
    Keyboard* keyboard = Keyboard::Get();
    
    if (keyboard->IsKeyPressed('C'))
    {
        // rigid_body_->SetVelocity(Math::Vector2::Zero());
        rigid_body_->AddForce(Math::Vector2::Up() * 5.f, ForceMode::kImpulse);
    }
    
    if (keyboard->IsKeyPressed('Z'))
    {
        Box* box = new Box(L"Box");
        box->GetTransform()->SetRelativePosition(GetTransform()->GetWorldPosition());
        SpawnActor(box);
    }

    TransformComponent* transform = GetTransform();
    Math::Vector2 world_position = Renderer::Get()->ConvertWorldToScreen(transform->GetWorldPosition());
    text_block_->SetPosition(world_position);
}
