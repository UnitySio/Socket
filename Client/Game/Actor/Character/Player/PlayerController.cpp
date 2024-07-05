#include "PlayerController.h"

#include "GameInstance.h"
#include "Windows.h"
#include "Actor/Box.h"

#include "Actor/Component/BoxColliderComponent.h"
#include "Actor/Component/RigidBodyComponent.h"
#include "Actor/Component/InputComponent.h"
#include "Actor/Component/TransformComponent.h"
#include "box2d/b2_mouse_joint.h"
#include "Level/World.h"
#include "Misc/Debug.h"
#include "Physics/HitResult.h"
#include "Physics/Physics.h"
#include "Windows/DX/Shape.h"
#include "Windows/DX/Sprite.h"

PlayerController::PlayerController(const std::wstring& kName) : CharacterBase(kName), mouse_joint_(nullptr)
{
    input_ = CreateComponent<InputComponent>(L"Input");
    input_->RegisterKey(VK_RIGHT);
    input_->RegisterKey(VK_LEFT);
    input_->RegisterKey('C');
    input_->RegisterKey('Z');
    input_->RegisterKey(MK_LBUTTON);
    
    sprite_ = MAKE_SHARED<Sprite>();
    CHECK_IF(sprite_->Load(L".\\Game_Data\\spritesheet.png"), L"Failed to load texture");

    sprite_->Split(15, 3, {.5f, .45f});
    
    const std::vector<SpriteFrame>& frames = sprite_->GetFrames();

    const float width = sprite_->GetWidth() * frames[0].uv_scale.x / sprite_->GetPPU();
    const float height = sprite_->GetHeight() * frames[0].uv_scale.y / sprite_->GetPPU();
    const float pivot_x = width * frames[0].pivot.x;
    const float pivot_y = height * frames[0].pivot.y;

    shape_ = MAKE_SHARED<Shape>();
    shape_->SetVertices(sprite_->GetVertices());
    shape_->SetIndices(sprite_->GetIndices());
    shape_->SetTexture(sprite_);
    shape_->SetPosition(GetTransform()->GetWorldPosition());
    shape_->SetRotation(GetTransform()->GetWorldRotationZ());
    shape_->SetScale({width, height});
    shape_->SetUVOffset(frames[0].uv_offset);
    shape_->SetUVScale(frames[0].uv_scale);
    shape_->SetPivot({pivot_x, pivot_y});
    shape_->SetZOrder(1);

    b2BodyDef body_def;
    mouse_body_ = World::Get()->physics_world_->CreateBody(&body_def);
    
}

void PlayerController::PhysicsTick(float delta_time)
{
    CharacterBase::PhysicsTick(delta_time);
    
    float h = input_->IsKeyPressed(VK_RIGHT) - input_->IsKeyPressed(VK_LEFT);
    
    rigid_body_->SetVelocity({h * 6.f, rigid_body_->GetVelocity().y});
}

void PlayerController::Tick(float delta_time)
{
    CharacterBase::Tick(delta_time);
    
    if (input_->IsKeyDown('C'))
    {
        rigid_body_->SetVelocity(Math::Vector2::Zero());
        rigid_body_->AddForce(Math::Vector2::Up() * 5.f, ForceMode::kImpulse);
    }
    
    const Math::Vector2& mouse_pos = input_->GetMousePosition();
    Math::Vector2 world_pos = Renderer::Get()->ConvertScreenToWorld(mouse_pos);

    if (input_->IsKeyDown(MK_LBUTTON))
    {
        Actor* actor = nullptr;
        if (Physics::OverlapBox(world_pos, {.1f, .1f}, &actor))
        {
            if (!actor->body_ || actor->body_->GetType() == b2_staticBody) return;
            
            float a = 5.f;
            float b = .7f;

            b2Body* body = actor->body_;
            b2MouseJointDef def;
            def.bodyA = mouse_body_;
            def.bodyB = body;
            def.target = {world_pos.x, world_pos.y};
            def.maxForce = 1000.f * body->GetMass();
            b2LinearStiffness(def.stiffness, def.damping, a, b, def.bodyA, def.bodyB);

            mouse_joint_ = static_cast<b2MouseJoint*>(World::Get()->physics_world_->CreateJoint(&def));
            body_->SetAwake(true);
        }
    }

    if (input_->IsKeyPressed(MK_LBUTTON))
    {
        if (mouse_joint_)
        {
            mouse_joint_->SetTarget({world_pos.x, world_pos.y});
        }
    }

    if (input_->IsKeyUp(MK_LBUTTON))
    {
        if (mouse_joint_)
        {
            World::Get()->physics_world_->DestroyJoint(mouse_joint_);
            mouse_joint_ = nullptr;
        }
    }
    
    if (input_->IsKeyDown('Z'))
    {
        Box* box = new Box(L"Box");
        box->GetTransform()->SetRelativePosition(GetTransform()->GetWorldPosition());
        SpawnActor(box);
    }
}

void PlayerController::Render(float alpha)
{
    CharacterBase::Render(alpha);
    
    shape_->SetPosition(GetTransform()->GetWorldPosition());
    shape_->SetRotation(GetTransform()->GetWorldRotationZ());

    World::Get()->AddShape(shape_);
}
