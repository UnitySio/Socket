#include "World.h"

#include <algorithm>

#include "EventManager.h"
#include "Level.h"
#include "Map/MainMap.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
#include "Time/TimerManager.h"
#include "Windows/DX/Renderer.h"
#include "Windows/DX/Shape.h"
#include "Windows/DX/ShapeBatch.h"

World::World() :
    shape_batch_(nullptr),
    shapes_(),
    current_level_(nullptr),
    levels_(),
    fps_(0),
    window_(nullptr)
{
    shape_batch_ = MAKE_SHARED<ShapeBatch>();
    shape_batch_->Init();
    
    b2Vec2 gravity(0.f, -9.81f);
    physics_world_ = MAKE_UNIQUE<b2World>(gravity);
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

void World::Init(const SHARED_PTR<WindowsWindow>& window)
{
    window_ = window;
    
    AddLevel<MainMap>(LevelType::kDefault, L"Map 0");
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
    TimerManager::Get()->Tick(delta_time);
    
    if (current_level_)
    {
        current_level_->Tick(delta_time);
    }

    static float timer = 0.f;
    static int frame_count = 0;
    
    timer += delta_time;
    ++frame_count;

    if (timer >= 1.f)
    {
        fps_ = frame_count;

        frame_count = 0;
        timer = 0.f;
    }
}

void World::Render(float alpha)
{
    if (current_level_)
    {
        current_level_->Render(alpha);
        physics_world_->DebugDraw();
    }

    // 추후 개선 필요
    std::ranges::sort(shapes_, Shape::CompareZOrder);

    shape_batch_->DrawShapes(window_, shapes_);
    shapes_.clear();
}

void World::RenderUI()
{
    Viewport* viewport = Renderer::Get()->FindViewport(window_.get());
    
    const float kMS = 1000.f / fps_;
    
    wchar_t buffer[256];
    swprintf_s(buffer, L"FPS: %d(%.fms)", fps_, kMS);
    Renderer::Get()->DrawString(window_, buffer, {viewport->d3d_viewport.Width, 10.f}, {300.f, 100.f}, 24.f, {255, 255, 255, 255});
}

void World::DestroyActor()
{
    if (current_level_)
    {
        current_level_->DestroyActor();
    }
}



void World::AddShape(const SHARED_PTR<Shape>& shape)
{
    shapes_.push_back(shape);
}

void World::ObjectProcess()
{
    for (const auto& temp : spawnList_)
    {
        GetLevel()->AddActor(temp);
    }
    spawnList_.clear();

    for (const auto& temp : removeList_)
    {
        for (auto it = GetLevel()->actors_.begin(); it != GetLevel()->actors_.end(); ++it)
        {
            if (*it == temp)
                GetLevel()->actors_.erase(it);
            break;
        }
    }
    removeList_.clear();
}
