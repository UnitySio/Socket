#include "Level.h"

#include "Enums.h"
#include "World.h"

#include "Actor/Actor.h"

Level::Level(World* world, const std::wstring& kName) :
    world_(world),
    actors_(),
    debug_draw_()
{
    name_ = kName;
}

void Level::Unload(EndPlayReason type)
{
    for (const auto& actor : actors_)
    {
        actor->EndPlay(type);
    }

    actors_.clear();
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

void Level::Tick(float delta_time)
{
    for (const auto& actor : actors_)
    {
        if (!actor->is_active_ || actor->is_destroy_) continue;
        actor->Tick(delta_time);
    }
}

void Level::Render(float alpha)
{
    for (const auto& actor : actors_)
    {
        if (!actor->is_active_ || actor->is_destroy_) continue;
        actor->Render(alpha);
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
    actors_.push_back(std::shared_ptr<Actor>(actor));
}
