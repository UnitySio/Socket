#include "World.h"

#include "EventManager.h"
#include "Level.h"
#include "Graphics/Graphics.h"
#include "Input/InputManager.h"
#include "Map/MainMap.h"
#include "Map/TempMap.h"

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
    
    primitive_batch_ = std::make_unique<PrimitiveBatch>(Graphics::Get()->GetD3DDeviceContext());
}

void World::Init()
{
    AddLevel<MainMap>(LevelType::kDefault, L"Map 0");
    AddLevel<TempMap>(LevelType::kTemp, L"Map 1");

    OpenLevel(LevelType::kDefault);
}

void World::OpenLevel(LevelType type)
{
    if (current_level_)
    {
        current_level_->Unload(EndPlayReason::kLevelTransition);
    }

    current_level_ = levels_[static_cast<size_t>(type)].get();
    current_level_->Load();
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

void World::Tick(float delta_time)
{
    InputManager* input_manager = InputManager::Get();
    if (input_manager->IsKeyPressed(VK_F1))
    {
        EventManager::Get()->AddEvent(
            {
                EventType::kLevelTransition,
                static_cast<uintptr_t>(LevelType::kDefault)
            });
    }
    else if (input_manager->IsKeyPressed(VK_F2))
    {
        EventManager::Get()->AddEvent(
            {
                EventType::kLevelTransition,
                static_cast<uintptr_t>(LevelType::kTemp)
            });
    }
    
    if (current_level_)
    {
        current_level_->Tick(delta_time);
    }
}

void World::Render(float alpha)
{
    if (current_level_)
    {
        current_level_->Render(alpha);
        
        primitive_batch_->Begin(Graphics::Get()->GetCamera2D().GetWorldMatrix() * Graphics::Get()->GetCamera2D().GetOrthographicMatrix());
        physics_world_->DebugDraw();
        primitive_batch_->End();
    }
}

void World::DestroyActor()
{
    if (current_level_)
    {
        current_level_->DestroyActor();
    }
}
