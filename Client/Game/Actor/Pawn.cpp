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
#include "Actor/Component/SpriteRendererComponent.h"
#include "Actor/Component/AnimatorComponent.h"
#include "Level/World.h"
#include "Time/TimerManager.h"
#include "Windows/DX/Shape.h"
#include "Windows/DX/Sprite.h"
#include "Windows/DX/Texture.h"
#include "Misc/Function.h"

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
    input_->RegisterKey(0x41);

    box_collider_ = CreateComponent<BoxColliderComponent>(L"BoxCollider");
    box_collider_->SetSize({ 1.f, 1.f });

    rigid_body_ = CreateComponent<RigidBodyComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kDynamic);
    rigid_body_->SetFreezeRotation(false);

    audio_listener_ = CreateComponent<AudioListenerComponent>(L"AudioListener");

    sprite_ = MAKE_SHARED<Sprite>();
    CHECK_IF(sprite_->Load(L".\\Game_Data\\spritesheet.png"), L"Failed to load texture");

    sprite_->Split(15, 3, { .5f, .5f });

    sprite_->SetWrapMode(WrapMode::kClamp);
    sprite_->SetFilterMode(FilterMode::kPoint);

    sprite_renderer_ = CreateComponent<SpriteRendererComponent>(L"SpriteRenderer");
    sprite_renderer_->SetRenderTarget(sprite_);

    //component setting
    animator_ = CreateComponent<AnimatorComponent>(L"Animator");
    animator_->sprite_renderer_ = sprite_renderer_;

    //clip option
    int temp[] = { 0, 1, 2, 3, 4, 5 };
    animator_->MakeAnimationClip(L"Idle", temp, 6);
    animator_->clips_[L"Idle"]->SetRepeat();
    animator_->clips_[L"Idle"]->SetPlaySpeed(6.f);
    animator_->playing_clip_ = animator_->clips_[L"Idle"];

    animator_->MakeAnimationClip(L"Attack", 7, 30);
    animator_->clips_[L"Attack"]->SetPlaySpeed(10.f);

    Function<int(int, int)> test(this, &Pawn::Test, 3, 5);
    //animator_->clips_[L"Idle"]->MakeTrigger(L"IsGoAtttack", L"Attack", std::move(test));

    Function<void(void)> attack(this, &Pawn::Attack);
    animator_->clips_[L"Idle"]->MakeTrigger(L"IsGoAtttack", L"Attack", std::move(attack));
    
    Function<void(void)> finish(this, &Pawn::EndAttack);
    animator_->clips_[L"Attack"]->MakeTrigger(L"IsEndAtttack", L"Idle", std::move(finish));

    animator_->clips_[L"Attack"]->SetTrigger(L"IsEndAtttack", true);
    animator_->clips_[L"Idle"]->SetTrigger(L"IsGoAtttack", false);
    
    
    animator_->clips_[L"Idle"]->triggers_[L"IsGoAtttack"].hasExitTime = false;
    
    /////////////////////////////////////////////////////////

    delegate_.Add([](const std::wstring& kStr) -> void {});
    
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

    if (input_->IsKeyDown(0x41))
    {
        animator_->clips_[L"Idle"]->SetTrigger(L"IsGoAtttack", true);
    }

    animator_->Tick(delta_time);
}

void Pawn::Render(float alpha)
{
    Actor::Render(alpha);

    const std::vector<SpriteFrame>& frames = sprite_renderer_->sprite_->GetFrames();

    const float width = sprite_renderer_->sprite_->GetWidth() * frames[sprite_renderer_->GetFrameIndex()].uv_scale.x / sprite_renderer_->sprite_->GetPPU();
    const float height = sprite_renderer_->sprite_->GetHeight() * frames[sprite_renderer_->GetFrameIndex()].uv_scale.y / sprite_renderer_->sprite_->GetPPU();
    const float pivot_x = width * frames[sprite_renderer_->GetFrameIndex()].pivot.x;
    const float pivot_y = height * frames[sprite_renderer_->GetFrameIndex()].pivot.y;

    SHARED_PTR<Shape> shape = MAKE_SHARED<Shape>();
    shape->SetVertices(sprite_renderer_->sprite_->GetVertices());
    shape->SetIndices(sprite_renderer_->sprite_->GetIndices());
    shape->SetTexture(sprite_renderer_->sprite_);
    shape->SetPosition(GetTransform()->GetWorldLocation());
    shape->SetRotation(GetTransform()->GetWorldRotationZ());
    shape->SetScale({width * dir_, height});
    shape->SetUVOffset(frames[sprite_renderer_->GetFrameIndex()].uv_offset);
    shape->SetUVScale(frames[sprite_renderer_->GetFrameIndex()].uv_scale);
    shape->SetPivot({pivot_x, pivot_y});
    shape->SetZOrder(1);

    World::Get()->AddShape(shape);
    
}

void Pawn::EndPlay(EndPlayReason type)
{
    Actor::EndPlay(type);

    if (type == EndPlayReason::kDestroyed)
    {
        std::wcout << L"Destroyed: " << GetName() << std::endl;
    }
    else if (type == EndPlayReason::kLevelTransition)
    {
        std::wcout << L"Transition: " << GetName() << std::endl;
    }
    else if (type == EndPlayReason::kQuit)
    {
        // 외부에 txt 파일 생성
        std::filesystem::path path = std::filesystem::current_path() / "log.txt";
        std::wofstream file(path, std::ios::app);
        file << L"Quit: " << GetName() << std::endl;
        file.close();
    }
}


void Pawn::Attack()
{
    animator_->clips_[L"Idle"]->SetTrigger(L"IsGoAtttack", false);
}

void Pawn::EndAttack()
{
    
}