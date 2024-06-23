#include "Pawn.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "Windows.h"

#include "Enums.h"
#include "Actor/Component/InputComponent.h"
#include "Actor/Component/BoxColliderComponent.h"
#include "Actor/Component/RigidBodyComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Actor/Component/AudioListenerComponent.h"
#include "Level/World.h"
#include "Time/TimerManager.h"
#include "Windows/DX/Shape.h"
#include "Windows/DX/Sprite.h"
#include "Windows/DX/Texture.h"

Pawn::Pawn(const std::wstring& kName) :
    Actor(kName),
    dir_(1),
    timer_(0.f),
    frame_index_(0)
{
    input_ = CreateComponent<InputComponent>(L"Input");
    input_->RegisterKey(VK_RIGHT);
    input_->RegisterKey(VK_LEFT);
    input_->RegisterKey(VK_SPACE);
    
    box_collider_ = CreateComponent<BoxColliderComponent>(L"BoxCollider");
    box_collider_->SetSize({1.f, 1.f});

    rigid_body_ = CreateComponent<RigidBodyComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kDynamic);
    rigid_body_->SetFreezeRotation(true);
    
    audio_listener_ = CreateComponent<AudioListenerComponent>(L"AudioListener");

    sprite_ = MAKE_SHARED<Sprite>();
    CHECK_IF(sprite_->Load(L".\\Game_Data\\spritesheet.png"), L"Failed to load texture");

    sprite_->Split(15, 3, {.5f, .45f});
    
}

void Pawn::BeginPlay()
{
    Actor::BeginPlay();
    
}

void Pawn::PhysicsTick(float delta_time)
{
    Actor::PhysicsTick(delta_time);

    float h = input_->IsKeyPressed(VK_RIGHT) - input_->IsKeyPressed(VK_LEFT);
    
    rigid_body_->SetVelocity({h * 2.f, rigid_body_->GetVelocity().y});

    if (h != 0) dir_ = h > 0 ? -1 : 1;
    
}

void Pawn::Tick(float delta_time)
{
    Actor::Tick(delta_time);
    
    if (input_->IsKeyDown(VK_SPACE))
    {
        rigid_body_->SetVelocity(Math::Vector2::Zero());
        rigid_body_->AddForce(Math::Vector2::Up() * 5.f, ForceMode::kImpulse);
    }

    timer_ += delta_time;
    if (timer_ >= 1.f / 8.f)
    {
        frame_index_ = (frame_index_ + 1) % 6;
        timer_ = 0.f;
    }
    
}

void Pawn::Render(float alpha)
{
    Actor::Render(alpha);

    const std::vector<SpriteFrame>& frames = sprite_->GetFrames();

    const float width = sprite_->GetWidth() * frames[frame_index_].uv_scale.x / sprite_->GetPPU();
    const float height = sprite_->GetHeight() * frames[frame_index_].uv_scale.y / sprite_->GetPPU();
    const float pivot_x = width * frames[frame_index_].pivot.x;
    const float pivot_y = height * frames[frame_index_].pivot.y;

    SHARED_PTR<Shape> shape = MAKE_SHARED<Shape>();
    shape->SetVertices(sprite_->GetVertices());
    shape->SetIndices(sprite_->GetIndices());
    shape->SetTexture(sprite_);
    shape->SetPosition(GetTransform()->GetWorldPosition());
    shape->SetRotation(GetTransform()->GetWorldRotationZ());
    shape->SetScale({width * dir_, height});
    shape->SetUVOffset(frames[frame_index_].uv_offset);
    shape->SetUVScale(frames[frame_index_].uv_scale);
    shape->SetPivot({pivot_x, pivot_y});
    shape->SetZOrder(1);

    World::Get()->AddShape(shape);
    
}
