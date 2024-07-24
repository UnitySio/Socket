#include "pch.h"
#include "Level.h"

#include "Enums.h"
#include "World.h"

#include "Actor/Actor.h"
#include "Audio/AudioManager.h"
#include "Logger/Logger.h"

Level::Level(const std::wstring& kName) :
    actors_(),
    debug_draw_()
{
    name_ = kName;
}

void Level::Unload(EndPlayReason type)
{
    AudioManager::Get()->StopAllSounds();
    
    for (const auto& actor : actors_)
    {
        actor->EndPlay(type);
    }

    actors_.clear();

    if (type == EndPlayReason::kLevelTransition)
    {
        LOG(L"Level Transition");
    }
    else if (type == EndPlayReason::kQuit)
    {
        LOG(L"Game Quit");
    }
    else if (type == EndPlayReason::kDestroyed)
    {
        LOG(L"Actor Destroyed");
    }
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

void Level::PostTick(float delta_time)
{
    for (const auto& actor : actors_)
    {
        if (!actor->is_active_ || actor->is_destroy_) continue;
        actor->PostTick(delta_time);
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

void Level::AddActor(const std::shared_ptr<Actor>& actor)
{
    actors_.push_back(actor);
}
