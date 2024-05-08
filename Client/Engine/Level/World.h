﻿#pragma once
#include "DebugDraw.h"
#include "Enums.h"
#include "Singleton.h"
#include "box2d/b2_world.h"
#include "Listener/ContactListener.h"

class Shape;
class ShapeBatch;
class WindowsWindow;
enum class LevelType : size_t;
class Level;

class World
{
public:
    World(const SharedPtr<WindowsWindow>& window);
    ~World() = default;

    void Init();
    void OpenLevel(LevelType type);
    void PhysicsTick(float delta_time);
    void Tick(float delta_time);
    void Render(float alpha);
    void DestroyActor();

    template<std::derived_from<Level> T>
    T* AddLevel(LevelType type, std::wstring name);

    inline WindowsWindow* GetWindow() const { return window_.get(); }
    inline Level* GetLevel() const { return current_level_; }

    void AddShape(const SharedPtr<Shape>& shape);

private:
    friend class Physics;
    friend class Level;
    friend class Actor;

    SharedPtr<WindowsWindow> window_;
    SharedPtr<ShapeBatch> shape_batch_;
    
    std::vector<SharedPtr<Shape>> shapes_;
    
    UniquePtr<b2World> physics_world_;
    
    ContactListener contact_listener_;
    
    DebugDraw debug_draw_;
    
    Level* current_level_;
    SharedPtr<Level> levels_[static_cast<size_t>(LevelType::kEnd)];
    
};

template <std::derived_from<Level> T>
T* World::AddLevel(LevelType type, std::wstring name)
{
    levels_[static_cast<size_t>(type)] = MakeShared<T>(this, name);
    return static_cast<T*>(levels_[static_cast<size_t>(type)].get());
}
