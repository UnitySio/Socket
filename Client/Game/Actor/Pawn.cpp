#include "Pawn.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "Enums.h"
#include "EventManager.h"
#include "Actor/Component/BoxColliderComponent.h"
#include "Actor/Component/RigidBodyComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Actor/Component/AudioListenerComponent.h"
#include "Actor/Component/SpriteRendererComponent.h"
#include "box2d/b2_fixture.h"
#include "Graphics/Graphics.h"
#include "imgui/imgui.h"
#include "Input/InputManager.h"
#include "Physics/HitResult.h"
#include "Physics/Physics.h"
#include "Time/Time.h"

Pawn::Pawn(const std::wstring& kName) :
    Actor(kName),
    box_collider_(nullptr),
    rigid_body_(nullptr),
    sprite_renderer_(nullptr)
{
    box_collider_ = CreateComponent<BoxColliderComponent>(L"BoxCollider");
    box_collider_->SetOffset({ 0.f, 1.45f });
    box_collider_->SetSize({ 1.f, 1.f });

    rigid_body_ = CreateComponent<RigidBodyComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kDynamic);
    rigid_body_->SetFreezeRotation(false);

    GetTransform()->SetRelativeLocation({ 1.f, 5.f });

    audio_listener_ = CreateComponent<AudioListenerComponent>(L"AudioListener");

    sprite_renderer_ = CreateComponent<SpriteRendererComponent>(L"SpriteRenderer");
}

void Pawn::PhysicsTick(float delta_time)
{
    Actor::PhysicsTick(delta_time);

    InputManager* input = InputManager::Get();
    float h = input->IsKeyPressed(VK_RIGHT) - input->IsKeyPressed(VK_LEFT);
    if (h != 0) rigid_body_->SetVelocity({ h * 2.f, rigid_body_->GetVelocity().y });

    if (h > 0) sprite_renderer_->SetFlipX(false);
    else if (h < 0) sprite_renderer_->SetFlipX(true);

    Math::Vector2 start = GetTransform()->GetWorldLocation() + Math::Vector2(0.f, 1.45f);
    const Math::Vector2 end = start + Math::Vector2(0.f, -1.f);

    HitResult hit_result;
    bool is_hit = Physics::RayCastSingle(hit_result, start, end, ActorLayer::kFloor);
    if (is_hit)
    {
        std::wcout << L"Hit: " << hit_result.actor->GetName() << std::endl;
    }

    std::vector<HitResult> hit_results;
    is_hit = Physics::RayCastMulti(hit_results, start, end, ActorLayer::kFloor | ActorLayer::kDefault);

    int a = 0;

}

void Pawn::Tick(float delta_time)
{
    Actor::Tick(delta_time);

    InputManager* input = InputManager::Get();

    if (input->IsKeyDown(VK_UP))
    {
        rigid_body_->SetVelocity(Math::Vector2::Zero());
        rigid_body_->AddForce(Math::Vector2::Up() * 5.f, ForceMode::kImpulse);
    }

    if (input->IsKeyDown(VK_SPACE))
    {
        EventManager::Get()->AddEvent(
            {
                EventType::kLevelTransition,
                static_cast<uintptr_t>(LevelType::kTemp)
            });
    }

}

void Pawn::Render(float alpha)
{
    Actor::Render(alpha);

    sprite_renderer_->RenderSprite();   
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