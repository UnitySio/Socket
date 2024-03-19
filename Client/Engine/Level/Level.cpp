#include "Level.h"

#include <iostream>

#include "box2d/b2_math.h"
#include "box2d/b2_world.h"

#include "Actor/Actor.h"
#include "box2d/b2_contact.h"
#include "Graphics/Graphics.h"

Level::Level(const std::wstring& kName) :
    world_(nullptr),
    actors_(),
    debug_draw_(),
    screen_position_(Vector::Zero())
{
    name_ = kName;

    b2Vec2 gravity(0.f, 9.81f * 100.f);
    world_ = std::make_unique<b2World>(gravity);
    world_->SetContactListener(&contact_listener_);

    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    flags += b2Draw::e_jointBit;
    // flags += b2Draw::e_aabbBit;
    // flags += b2Draw::e_pairBit;
    // flags += b2Draw::e_centerOfMassBit;
    debug_draw_.SetFlags(flags);

    world_->SetDebugDraw(&debug_draw_);

    primitive_batch_ = std::make_unique<PrimitiveBatch>(Graphics::Get()->GetD3DDeviceContext());
}

void Level::BeginPlay()
{
    for (const auto& actor : actors_)
    {
        actor->BeginPlay();
    }
}

void Level::PhysicsTick(float delta_time)
{
    for (const auto& actor : actors_)
    {
        if (!actor->is_active_ || actor->is_destroy_) continue;

        b2Vec2 position = actor->body_->GetPosition();
        actor->previous_location_ = {position.x, position.y};
        actor->previous_angle_ = actor->body_->GetAngle();
    }

    world_->Step(delta_time, 8, 3);

    contact_listener_.Tick();

    for (const auto& actor : actors_)
    {
        if (!actor->is_active_ || actor->is_destroy_) continue;
        actor->PhysicsTick(delta_time);
    }
}

void Level::Interpolate(float alpha)
{
    for (b2Body* body = world_->GetBodyList(); body; body = body->GetNext())
    {
        if (body->GetType() == b2_staticBody) continue;

        const Actor* actor = reinterpret_cast<Actor*>(body->GetUserData().pointer);
        if (!actor) continue;

        const b2Vec2 position = body->GetPosition();
        const b2Vec2 previous_position = {actor->previous_location_.x, actor->previous_location_.y};

        b2Vec2 interpolated_position = {
            position.x * alpha + previous_position.x * (1.f - alpha),
            position.y * alpha + previous_position.y * (1.f - alpha)
        };

        const float interpolated_angle = body->GetAngle() * alpha + actor->previous_angle_ * (1.f - alpha);

        // body->SetTransform(interpolated_position, interpolated_angle);
    }
}

void Level::Tick(float delta_time)
{
    for (const auto& actor : actors_)
    {
        if (!actor->is_active_ || actor->is_destroy_) continue;
        actor->Tick(delta_time);
    }
}

void Level::EndPlay()
{
    for (const auto& actor : actors_)
    {
        actor->EndPlay();
    }
}

void Level::Render()
{
    for (const auto& actor : actors_)
    {
        if (!actor->is_active_ || actor->is_destroy_) continue;
        actor->Render();
    }

    primitive_batch_->Begin(Graphics::Get()->GetCamera2D().GetWorldMatrix() * Graphics::Get()->GetCamera2D().GetOrthographicMatrix());
    world_->DebugDraw();
    primitive_batch_->End();
}

void Level::Destroy()
{
    for (auto iter = actors_.begin(); iter != actors_.end();)
    {
        if ((*iter)->is_destroy_)
        {
            (*iter)->EndPlay();
            iter = actors_.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

void Level::AddActor(Actor* actor)
{
    actors_.push_back(std::unique_ptr<Actor>(actor));
}

b2Vec2 Level::GetRenderPosition(b2Vec2 world_position)
{
    const b2Vec2 screen_position = {screen_position_.x, screen_position_.y};
    return world_position - screen_position;
}

b2Vec2 Level::GetWorldPosition(b2Vec2 render_position)
{
    const b2Vec2 screen_position = {screen_position_.x, screen_position_.y};
    return render_position + screen_position;
}
