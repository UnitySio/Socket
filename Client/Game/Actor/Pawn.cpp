#include "Pawn.h"

#include "Dummy.h"
#include "Actor/Component/BoxColliderComponent.h"
#include "Actor/Component/RigidBodyComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "Actor/Component/AudioListenerComponent.h"
#include "Graphics/Graphics.h"
#include "imgui/imgui.h"
#include "Input/InputManager.h"
#include "Time/Time.h"

Pawn::Pawn(b2World* world, const std::wstring& kName) :
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
    rigid_body_->SetFreezeRotation(true);
    
    GetTransform()->SetRelativeLocation({1.f, 5.f});

    Graphics* gfx = Graphics::Get();
    
    sprite_ = std::make_unique<Sprite>(L"Knight", 32, Vector(0.f, 0.f));
    assert(sprite_->Load(gfx->GetD3DDevice(), L".\\spritesheet.png"));
    
    sprite_->Split(3, 15, {.45f, 0.f});
    
    audio_listener_ = CreateComponent<AudioListenerComponent>(L"AudioListener");
    
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
        dummy->GetTransform()->SetRelativeLocation(GetTransform()->GetRelativeLocation());
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

    const Vector location = GetTransform()->GetRelativeLocation();
    const float angle = GetTransform()->GetRelativeRotationZ();
    batch->Draw(sprite_.get(), L"Knight_" + std::to_wstring(idx), location, {1.f * -dir_, 1.f}, angle);

    const Vector world_location = GetTransform()->GetWorldLocation();
    
    ImGui::Begin("Pawn");
    ImGui::Text("Location: %.2f, %.2f", world_location.x, world_location.y);
    ImGui::End();
    
}
