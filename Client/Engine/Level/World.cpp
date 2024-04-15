#include "World.h"

#include "Level.h"
#include "Map/MainMap.h"

World::World() :
    current_level_(nullptr),
    levels_{}
{
    b2Vec2 gravity(0.f, -9.81f);
    physics_world_ = std::make_unique<b2World>(gravity);
    physics_world_->SetContactListener(&contact_listener_);
    
    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    // flags += b2Draw::e_jointBit;
    // flags += b2Draw::e_aabbBit;
    // flags += b2Draw::e_pairBit;
    // flags += b2Draw::e_centerOfMassBit;
    debug_draw_.SetFlags(flags);

    physics_world_->SetDebugDraw(&debug_draw_);
}

void World::Init()
{
    AddLevel<MainMap>(LevelType::kDefault, L"MainMap");

    OpenLevel(LevelType::kDefault);
}

void World::OpenLevel(LevelType type)
{
    if (current_level_)
    {
        current_level_->EndPlay(EndPlayReason::kLevelTransition);
    }

    current_level_ = levels_[static_cast<size_t>(type)].get();
    current_level_->InitializeActors();
}

void World::PhysicsTick(float delta_time)
{
    if (current_level_)
    {
        physics_world_->Step(delta_time, 8, 3);
        contact_listener_.Tick();
        
        current_level_->PhysicsTick(delta_time);
    }
}

void World::Interpolate(float alpha)
{
    if (current_level_)
    {
        current_level_->Interpolate(alpha);
    }
}

void World::Tick(float delta_time)
{
    if (current_level_)
    {
        current_level_->Tick(delta_time);
    }
}

void World::Render()
{
    if (current_level_)
    {
        current_level_->Render();
    }
}

void World::DestroyActor()
{
    if (current_level_)
    {
        current_level_->DestroyActor();
    }
}
