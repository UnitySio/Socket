#include "pch.h"
#include "World.h"

#include <algorithm>

#include "EventManager.h"
#include "GameInstance.h"
#include "Level.h"
#include "Actor/FollowCamera.h"
#include "Actor/Component/CameraComponent.h"
#include "imgui/imgui.h"
#include "Input/Keyboard.h"
#include "Logger/Logger.h"
#include "Map/MainMap.h"
#include "Map/SplashMap.h"
#include "Map/WorldMap.h"
#include "Math/Color.h"
#include "Math/Vector2.h"
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
    levels_()
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
    
    AddLevel<MainMap>(LevelType::kDefault, L"Map 0");
    AddLevel<WorldMap>(LevelType::kWorld, L"Map 1");
    AddLevel<SplashMap>(LevelType::kSplash, L"Splash");
    
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

    Keyboard* keyboard = Keyboard::Get();
    if (keyboard->IsKeyPressed(VK_F1))
    {
        OpenLevel(LevelType::kDefault);
    }

    if (keyboard->IsKeyPressed(VK_F2))
    {
        OpenLevel(LevelType::kWorld);
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

void World::DestroyActor()
{
    if (current_level_)
    {
        current_level_->DestroyActor();
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
    current_level_->Load();
    current_level_->InitializeActors();

    next_level_ = nullptr;
    
    swprintf_s(buffer, L"Body Count: %d", physics_world_->GetBodyCount());
    LOG(buffer);
}
