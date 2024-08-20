#include "pch.h"
#include "World.h"

#include <algorithm>

#include "Level.h"
#include "Actor/FollowCamera.h"
#include "Actor/Component/CameraComponent.h"
#include "imgui/imgui.h"
#include "Input/Keyboard.h"
#include "Logger/Logger.h"
#include "Map/MainMap.h"
#include "Map/MainMenu.h"
#include "Map/SplashMap.h"
#include "Time/TimerManager.h"
#include "UI/Canvas.h"
#include "Windows/DX/Renderer.h"
#include "Windows/DX/Shape.h"
#include "Windows/DX/ShapeBatch.h"

World::World() :
    window_(nullptr),
    shape_batch_(nullptr),
    shapes_(),
    current_level_(nullptr),
    next_level_(nullptr),
    levels_(),
    pending_actors_()
{
    shape_batch_ = std::make_shared<ShapeBatch>();
    shape_batch_->Init();
    
    b2Vec2 gravity(0.f, -9.81f);
    physics_world_ = std::make_unique<b2World>(gravity);
    physics_world_->SetContactListener(&contact_listener_);
    
    uint32 flags = 0;
    // flags += b2Draw::e_shapeBit;
    // flags += b2Draw::e_jointBit;
    // flags += b2Draw::e_aabbBit;
    // flags += b2Draw::e_pairBit;
    // flags += b2Draw::e_centerOfMassBit;
    debug_draw_.SetFlags(flags);

    physics_world_->SetDebugDraw(&debug_draw_);
    
}

void World::Init(const std::shared_ptr<WindowsWindow>& kWindow)
{
    window_ = kWindow;
    
    AddLevel<SplashMap>(LevelType::kSplash, L"Splash");
    AddLevel<MainMenu>(LevelType::kMainMenu, L"Main Menu");
    AddLevel<MainMap>(LevelType::kDefault, L"Unknown");
    
    OpenLevel(LevelType::kSplash);
}

void World::OpenLevel(LevelType type)
{
    next_level_ = levels_[static_cast<size_t>(type)].get();
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
}

void World::PostTick(float delta_time)
{
    if (current_level_)
    {
        current_level_->PostTick(delta_time);
    }
}

void World::Render(float alpha)
{
    if (current_level_)
    {
        current_level_->Render(alpha);
        physics_world_->DebugDraw();
    }

    std::vector<std::shared_ptr<Shape>> shapes;

    if (const std::shared_ptr<Actor> actor = camera_.lock())
    {
        if (FollowCamera* camera = dynamic_cast<FollowCamera*>(actor.get()))
        {
            Bounds bounds = camera->GetCamera()->GetBounds();

            for (const auto& shape : shapes_)
            {
                if (Bounds::Contains(bounds, shape->GetBounds()))
                {
                    shapes.push_back(shape);
                }
            }
        }
    }
    
    std::ranges::sort(shapes, Shape::CompareZOrder);
    shapes_.clear();
    
    shape_batch_->DrawShapes(window_, shapes);
}

void World::DestroyActors()
{
    if (current_level_)
    {
        current_level_->DestroyActors();
    }
}

void World::AddShape(const std::shared_ptr<Shape>& kShape)
{
    shapes_.push_back(kShape);
}

void World::TransitionLevel()
{
    if (!next_level_) return;
    
    WCHAR buffer[256];
    swprintf_s(buffer, L"Body Count: %d", physics_world_->GetBodyCount());
    LOG(buffer);
    
    if (current_level_)
    {
        current_level_->Unload(EndPlayReason::kLevelTransition);
        Canvas::Get()->Clear();
    }

    current_level_ = next_level_;
    next_level_ = nullptr;
    
    current_level_->Load();
    current_level_->InitializeActors();
    
    SetWindowText(window_->GetHWnd(), current_level_->GetName().c_str());
    
    swprintf_s(buffer, L"Body Count: %d", physics_world_->GetBodyCount());
    LOG(buffer);
}

void World::SpawnActors()
{
    for (const auto& actor : pending_actors_)
    {
        current_level_->actors_.push_back(actor);
        actor->BeginPlay();
    }

    pending_actors_.clear();
}

void World::DestroyActor(Actor* actor)
{
    actor->is_pending_deletion_ = true;
    actor->Destroyed();
}
