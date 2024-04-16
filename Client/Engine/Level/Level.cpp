#include "Level.h"

#include <iostream>

#include "Enums.h"
#include "World.h"
#include "box2d/b2_math.h"
#include "box2d/b2_world.h"

#include "Actor/Actor.h"
#include "box2d/b2_contact.h"
#include "Graphics/Graphics.h"

Level::Level(const std::wstring& kName) :
    actors_(),
    debug_draw_()
{
    name_ = kName;
}

void Level::InitializeActors()
{
    for (const auto& actor : actors_)
    {
        actor->PreInitializeComponents();
    }
    
    for (const auto& actor : actors_)
    {
        actor->InitializeComponents();
        actor->PostInitializeComponents();
    }
    
    for (const auto& actor : actors_)
    {
        actor->BeginPlay();
    }
}

void Level::PhysicsTick(float delta_time)
{
    // for (const auto& actor : actors_)
    // {
    //     if (!actor->is_active_ || actor->is_destroy_) continue;
    //
    //     b2Vec2 position = actor->body_->GetPosition();
    //     actor->previous_location_ = {position.x, position.y};
    //     actor->previous_angle_ = actor->body_->GetAngle();
    // }

    for (const auto& actor : actors_)
    {
        if (!actor->is_active_ || actor->is_destroy_) continue;
        actor->PhysicsTick(delta_time);
    }
}

void Level::Interpolate(float alpha)
{
    const World* world = World::Get();
    for (b2Body* body = world->physics_world_->GetBodyList(); body; body = body->GetNext())
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

void Level::EndPlay(EndPlayReason type)
{
    for (const auto& actor : actors_)
    {
        actor->EndPlay(type);
    }
}

void Level::Render()
{
    for (const auto& actor : actors_)
    {
        if (!actor->is_active_ || actor->is_destroy_) continue;
        actor->Render();
    }
}

void Level::DestroyActor()
{
    for (auto iter = actors_.begin(); iter != actors_.end();)
    {
        if ((*iter)->is_destroy_)
        {
            (*iter)->Destroyed();
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
