#include "TransformComponent.h"

#include "Actor/Actor.h"
#include "box2d/b2_body.h"
#include "Graphics/Graphics.h"
#include "Graphics/PrimitiveBatch.h"
#include "Level/Level.h"
#include "Level/World.h"
#include "RigidBodyComponent.h"

TransformComponent::TransformComponent(Actor* owner, const std::wstring& kName) :
    ActorComponent(owner, kName),
    world_location_(Vector::Zero()),
    world_scale_(Vector::One()),
    relative_location_(Vector::Zero()),
    relative_scale_(Vector::One()),
    world_rotation_z_(0.f),
    relative_rotation_z_(0.f)
{
}

void TransformComponent::TickComponent(float delta_time)
{
    ActorComponent::TickComponent(delta_time);

    const b2Body* body = GetOwner()->body_;
    if (!body || body->GetType() == b2_staticBody) return;
    
    if (!GetOwner()->parent_)
    {
        const b2Vec2 position = body->GetPosition();
        relative_location_ = {position.x, position.y};

        const float angle = body->GetAngle();
        relative_rotation_z_ = angle * 180.f / b2_pi;

        UpdateTransform();
        return;
    }

    const RigidBodyComponent* rigid_body = GetOwner()->GetComponent<RigidBodyComponent>();
    if (!rigid_body || rigid_body->GetBodyType() == b2_kinematicBody) return;

    const b2Vec2 position = body->GetPosition() - GetOwner()->parent_->body_->GetPosition();
    relative_location_ = {position.x, position.y};

    const float angle = body->GetAngle() - GetOwner()->parent_->body_->GetAngle();
    relative_rotation_z_ = angle * 180.f / b2_pi;
    
    UpdateTransform();
}

void TransformComponent::Render()
{
    ActorComponent::Render();

    // 테스트 코드 (추후 제거)
    const Level* level = World::Get()->GetLevel();
    if (!level) return;

    PrimitiveBatch* batch = level->GetPrimitiveBatch();
    if (!batch) return;

    const Vector center = world_location_;
    const b2Color fill_color(1.f, 1.f, 1.f);

    batch->Begin(Graphics::Get()->GetCamera2D().GetWorldMatrix() * Graphics::Get()->GetCamera2D().GetOrthographicMatrix());
    
    std::vector<VertexPrimitive> vertices;
    vertices.push_back(VertexPrimitive(center.x, center.y, 0.f, fill_color.r, fill_color.g, fill_color.b, fill_color.a));
    
    for (int32 i = 0; i < 16; ++i)
    {
        constexpr float radius = .1f;
        float theta = 2.f * b2_pi * i / 16;
        float x = center.x + radius * cos(theta);
        float y = center.y + radius * sin(theta);
        vertices.push_back(VertexPrimitive(x, y, 0.f, fill_color.r, fill_color.g, fill_color.b, fill_color.a));
    }

    vertices.push_back(vertices[1]);

    std::vector<UINT> indices;
    for (int32 i = 0; i < 16; i++)
    {
        indices.push_back(0);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
    }
    
    batch->DrawSolidPolygon(vertices, indices);
    
    batch->End();
}

void TransformComponent::SetRelativeLocation(Vector location)
{
    relative_location_ = location;
    UpdateTransform();

    if (b2Body* body = GetOwner()->body_)
    {
        body->SetTransform({world_location_.x, world_location_.y}, world_rotation_z_ * GE_PI / 180.f);
    }
}

void TransformComponent::SetRelativeRotationZ(float angle)
{
    relative_rotation_z_ = angle;
    UpdateTransform();

    if (b2Body* body = GetOwner()->body_)
    {
        body->SetTransform({world_location_.x, world_location_.y}, world_rotation_z_ * GE_PI / 180.f);
    }
}

Vector TransformComponent::GetRightVector() const
{
    const float theta = relative_rotation_z_ * GE_PI / 180.f;
    const float c = cosf(theta);
    const float s = sinf(theta);

    return {c, s};
}

Vector TransformComponent::GetUpVector() const
{
    const float theta = relative_rotation_z_ * GE_PI / 180.f;
    const float c = cosf(theta);
    const float s = sinf(theta);

    return {-s, c};
}

void TransformComponent::UpdateTransform()
{
    if (GetOwner()->parent_)
    {
        Vector parent_location = GetOwner()->parent_->transform_->world_location_;
        const float parent_rotation = GetOwner()->parent_->transform_->world_rotation_z_;

        const float theta = parent_rotation * GE_PI / 180.f;
        const float c = cosf(theta);
        const float s = sinf(theta);

        const float x = relative_location_.x * c - relative_location_.y * s;
        const float y = relative_location_.x * s + relative_location_.y * c;

        world_location_ = parent_location + Vector(x, y);
        world_rotation_z_ = parent_rotation + relative_rotation_z_;

        const RigidBodyComponent* rigid_body = GetOwner()->GetComponent<RigidBodyComponent>();
        if (rigid_body)
        {
            if (rigid_body->GetBodyType() == b2_kinematicBody)
            {
                if (b2Body* body = GetOwner()->body_)
                {
                    body->SetTransform({world_location_.x, world_location_.y}, world_rotation_z_ * GE_PI / 180.f);
                }
            }
        }
    }
    else
    {
        world_location_ = relative_location_;
        world_rotation_z_ = relative_rotation_z_;
    }

    // 자식 Actor들의 Transform을 업데이트
    for (const auto& child : GetOwner()->children_)
    {
        child->transform_->UpdateTransform();
    }
}
