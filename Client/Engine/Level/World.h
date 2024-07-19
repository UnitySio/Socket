#pragma once
#include "DebugDraw.h"
#include "Enums.h"
#include "Singleton.h"
#include "box2d/b2_world.h"
#include "Listener/ContactListener.h"
#include "Windows/DX/Renderer.h"

class Actor;
class Shape;
class ShapeBatch;
class Level;

class World : public Singleton<World>
{
public:
    World();
    virtual ~World() override = default;

    void Init(const std::shared_ptr<WindowsWindow>& kWindow);
    void OpenLevel(LevelType type);
    void PhysicsTick(float delta_time);
    void Tick(float delta_time);
    void PostTick(float delta_time);
    void Render(float alpha);
    void RenderUI();
    void DestroyActor();
    void AddShape(const std::shared_ptr<Shape>& kShape);
    void TransitionLevel();

    template<std::derived_from<Level> T>
    T* AddLevel(LevelType type, std::wstring name);

    inline WindowsWindow* GetWindow() const { return window_.get(); }
    inline Level* GetLevel() const { return current_level_; }
    inline std::weak_ptr<Actor> GetCamera() const { return camera_; }

private:
    friend class Physics;
    friend class Level;
    friend class Actor;
    friend class TilemapComponent;
    friend class CameraComponent;
    friend class PlayerController;

    inline void SetCamera(const std::shared_ptr<Actor>& kCamera) { camera_ = kCamera; }

    std::shared_ptr<WindowsWindow> window_;
    
    std::shared_ptr<ShapeBatch> shape_batch_;
    
    std::vector<std::shared_ptr<Shape>> shapes_;
    
    std::unique_ptr<b2World> physics_world_;
    
    ContactListener contact_listener_;
    
    DebugDraw debug_draw_;
    
    Level* current_level_;
    Level* next_level_;
    
    std::shared_ptr<Level> levels_[static_cast<size_t>(LevelType::kEnd)];

    std::weak_ptr<Actor> camera_;
};

template <std::derived_from<Level> T>
T* World::AddLevel(LevelType type, std::wstring name)
{
    levels_[static_cast<size_t>(type)] = std::make_shared<T>(name);
    return static_cast<T*>(levels_[static_cast<size_t>(type)].get());
}
