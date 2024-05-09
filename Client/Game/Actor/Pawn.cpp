﻿#include "Pawn.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "Windows.h"

#include "Enums.h"
#include "Actor/Component/BoxColliderComponent.h"
#include "Actor/Component/RigidBodyComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Actor/Component/AudioListenerComponent.h"
#include "Input/Keyboard.h"

Pawn::Pawn(World* world, const std::wstring& kName) :
    Actor(world, kName),
    box_collider_(nullptr),
    rigid_body_(nullptr)
{
    box_collider_ = CreateComponent<BoxColliderComponent>(L"BoxCollider");
    box_collider_->SetOffset({0.f, 1.45f});
    box_collider_->SetSize({1.f, 1.f});

    rigid_body_ = CreateComponent<RigidBodyComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kDynamic);
    rigid_body_->SetFreezeRotation(false);
    
    audio_listener_ = CreateComponent<AudioListenerComponent>(L"AudioListener");
    
}

void Pawn::BeginPlay()
{
    Actor::BeginPlay();
    
}

void Pawn::PhysicsTick(float delta_time)
{
    Actor::PhysicsTick(delta_time);

    Keyboard* keyboard = Keyboard::Get();
    if (keyboard)
    {
        float h = keyboard->IsKeyPressed(VK_RIGHT) - keyboard->IsKeyPressed(VK_LEFT);
        float v = keyboard->IsKeyPressed(VK_DOWN) - keyboard->IsKeyPressed(VK_UP);

        rigid_body_->SetVelocity({h * 2.f, rigid_body_->GetVelocity().y});
    }
    
}

void Pawn::Tick(float delta_time)
{
    Actor::Tick(delta_time);
    
    Keyboard* keyboard = Keyboard::Get();
    if (keyboard->IsKeyDown(VK_SPACE))
    {
        rigid_body_->SetVelocity(Math::Vector2::Zero());
        rigid_body_->AddForce(Math::Vector2::Up() * 5.f, ForceMode::kImpulse);
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
