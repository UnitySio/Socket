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
#include "Windows/DX/Shape.h"
#include "Windows/DX/Texture.h"

Pawn::Pawn(const std::wstring& kName) :
    Actor(kName)
{
    input_ = CreateComponent<InputComponent>(L"Input");
    input_->RegisterKey(VK_RIGHT);
    input_->RegisterKey(VK_LEFT);
    input_->RegisterKey(VK_SPACE);
    
    box_collider_ = CreateComponent<BoxColliderComponent>(L"BoxCollider");
    box_collider_->SetSize({1.f, 1.f});

    rigid_body_ = CreateComponent<RigidBodyComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kDynamic);
    rigid_body_->SetFreezeRotation(false);
    
    audio_listener_ = CreateComponent<AudioListenerComponent>(L"AudioListener");

    texture_ = MAKE_SHARED<Texture>();
    CHECK_IF(texture_->Load(L".\\Game_Data\\spritesheet.png"), L"Failed to load texture");

    texture_->SetFilterMode(FilterMode::kPoint);
    
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
    
}

void Pawn::Tick(float delta_time)
{
    Actor::Tick(delta_time);
    
    if (input_->IsKeyDown(VK_SPACE))
    {
        rigid_body_->SetVelocity(Math::Vector2::Zero());
        rigid_body_->AddForce(Math::Vector2::Up() * 5.f, ForceMode::kImpulse);
    }
    
}

void Pawn::Render(float alpha)
{
    Actor::Render(alpha);

    SHARED_PTR<Shape> shape = MAKE_SHARED<Shape>();
    shape->SetVertices(texture_->GetVertices());
    shape->SetIndices(texture_->GetIndices());
    shape->SetTexture(texture_);
    shape->SetPosition({0.f, 0.f});
    shape->SetScale({96.f, 16.f});
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
