﻿#include "pch.h"
#include "Level.h"

#include "Enums.h"
#include "World.h"

#include "Actor/Actor.h"
#include "Actor/Camera.h"
#include "Audio/AudioManager.h"
#include "Event/Events.h"

Level::Level(const std::wstring& kName) :
    actors_(),
    has_begun_play_(false)
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
    
    has_begun_play_ = true;
}

void Level::PhysicsTick(float delta_time)
{
    for (const auto& actor : actors_)
    {
        if (!actor->is_active_) continue;
        actor->PhysicsTick(delta_time);
    }
}

void Level::Tick(float delta_time)
{
    for (const auto& actor : actors_)
    {
        if (!actor->is_active_) continue;
        actor->Tick(delta_time);
    }
}

void Level::PostTick(float delta_time)
{
    for (const auto& actor : actors_)
    {
        if (!actor->is_active_) continue;
        actor->PostTick(delta_time);
    }
}

void Level::Render(float alpha)
{
    for (const auto& actor : actors_)
    {
        if (!actor->is_active_) continue;
        actor->Render(alpha);
    }
}

void Level::OnEvent(const Event& event)
{
    if (has_begun_play_)
    {
        if (event.type == EventType::kWindowSize)
        {
            Camera::Get()->UpdateProjectionMatrix();
        }
    }
}
