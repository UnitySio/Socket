#include "Pawn.h"

#include <iostream>
#include <ostream>

#include "Dummy.h"
#include "../../Engine/Core.h"
#include "../../Engine/Actor/Component/SceneComponent/SceneComponent.h"
#include "../../Engine/Actor/Component/BoxColliderComponent.h"
#include "../../Engine/Actor/Component/RigidBodyComponent.h"
#include "../../Engine/Graphics/Graphics.h"
#include "../../Engine/Input/InputManager.h"
#include "../../Engine/Vector.h"
#include "../../Engine/Level/Level.h"

#include "../../Engine/Level/Listener/QueryCallback.h"
#include "box2d/b2_fixture.h"
#include "box2d/b2_world.h"

#include "Time/Time.h"


Pawn::Pawn(b2World* world, const std::wstring& kName) :
    Actor(world, kName),
    scene_(nullptr),
    box_collider_(nullptr),
    rigid_body_(nullptr),
    dir_(1)
{
    scene_ = CreateComponent<SceneComponent>(L"Scene");
    SetRootComponent(scene_);
    
    box_collider_ = CreateComponent<BoxColliderComponent>(L"BoxCollider");
    box_collider_->SetOffset({0.f, 1.45f});
    box_collider_->SetSize({1.f, 1.f});

    rigid_body_ = CreateComponent<RigidBodyComponent>(L"RigidBody");
    rigid_body_->SetBodyType(BodyType::kDynamic);
    // rigid_body_->SetFreezeRotation(true);
    
    SetActorLocation({1.f, 5.f});

    Graphics* gfx = Graphics::Get();
    
    sprite_ = std::make_unique<Sprite>(L"Knight", 32, Vector(0.f, 0.f));
    assert(sprite_->Load(gfx->GetD3DDevice(), L".\\spritesheet.png"));
    
    sprite_->Split(3, 15, {-.05f, -.5f});
    
}

void Pawn::PhysicsTick(float delta_time)
{
    Actor::PhysicsTick(delta_time);
    
    InputManager* input = InputManager::Get();
    float h = input->IsKeyPressed(VK_RIGHT) - input->IsKeyPressed(VK_LEFT);
    if (h != 0) rigid_body_->SetVelocity({h * 2.f, rigid_body_->GetVelocity().y});

    dir_ = h > 0 ? 1 : h < 0 ? -1 : dir_;
    
}

void Pawn::Tick(float delta_time)
{
    Actor::Tick(delta_time);

    InputManager* input = InputManager::Get();

    if (input->IsKeyDown(VK_UP))
    {
        rigid_body_->SetVelocity(Vector::Zero());
        rigid_body_->AddForce(Vector::Up() * 5.f, ForceMode::kImpulse);
    }

    if (input->IsKeyDown(VK_SPACE))
    {
        Dummy* dummy = new Dummy(GetWorld(), L"Dummy");
        dummy->GetRigidBody()->SetBodyType(BodyType::kDynamic);
        dummy->SetActorLocation({GetActorLocation().x, GetActorLocation().y});
        SpawnActor(dummy);
    }
    
}

void Pawn::Render()
{
    Actor::Render();

    Graphics* gfx = Graphics::Get();
    SpriteBatch* batch = gfx->GetSpriteBatch();

    static int idx = 0;

    static float time = 0.f;
    time += Time::DeltaTime();
    if (time > 1.f / 5.f)
    {
        idx = (idx + 1) % 6;
        time = 0.f;
    }

    batch->Draw(sprite_.get(), L"Knight_" + std::to_wstring(idx), GetActorLocation(), {1.f * -dir_, 1.f}, GetActorRotation());
    
}
