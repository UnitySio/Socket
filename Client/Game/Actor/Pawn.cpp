#include "Pawn.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "Enums.h"
#include "Actor/Component/BoxColliderComponent.h"
#include "Actor/Component/RigidBodyComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Actor/Component/AudioListenerComponent.h"
#include "Input/Keyboard.h"
#include "Windows.h"

Pawn::Pawn(World* world, const std::wstring& kName) :
    Actor(world, kName),
    box_collider_(nullptr),
    rigid_body_(nullptr),
    dir_(1)
{
    box_collider_ = CreateComponent<BoxColliderComponent>(L"BoxCollider");
    box_collider_->SetOffset({0.f, 1.45f});
    box_collider_->SetSize({1.f, 1.f});

    rigid_body_ = CreateComponent<RigidBodyComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kDynamic);
    rigid_body_->SetFreezeRotation(false);
    
    audio_listener_ = CreateComponent<AudioListenerComponent>(L"AudioListener");
    
}

void Pawn::PhysicsTick(float delta_time)
{
    Actor::PhysicsTick(delta_time);
    
}

void Pawn::Tick(float delta_time)
{
    Actor::Tick(delta_time);

    if (Keyboard::IsKeyDown(0))
    {
        OutputDebugString(L"Key 0 is down\n");
    }

    if (Keyboard::IsKeyPressed(0))
    {
        OutputDebugString(L"Key 0 was pressed\n");
    }

    if (Keyboard::IsKeyUp(0))
    {
        OutputDebugString(L"Key 0 was up\n");
    }
    
}

void Pawn::Render(float alpha)
{
    Actor::Render(alpha);
    
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

void Pawn::OnCollisionEnter(Actor* other)
{
    Actor::OnCollisionEnter(other);

    rigid_body_->SetVelocity(Math::Vector2::Zero());
    rigid_body_->AddForce(Math::Vector2::Up() * 5.f, ForceMode::kImpulse);
}
