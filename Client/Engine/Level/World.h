#pragma once
#include <queue>

#include "b2DebugDrawHelper.h"
#include "Enums.h"
#include "Singleton.h"
#include "Actor/Actor.h"
#include "box2d/box2d.h"
#include "Windows/DX/Renderer.h"

class Shape;
class ShapeBatch;
class Level;

class World : public Singleton<World>
{
public:
    World();
    virtual ~World() override;

    void Init(const std::shared_ptr<WindowsWindow>& kWindow);
    void OpenLevel(LevelType type);
    void PhysicsTick(float delta_time);
    void Tick(float delta_time);
    void PostTick(float delta_time);
    void Render(float alpha);
    void AddShape(const std::shared_ptr<Shape>& kShape);
    void TransitionLevel();
    void SpawnActors();

    template<std::derived_from<Actor> T>
    T* SpawnActor(const std::wstring& kName);

    template<std::derived_from<Level> T>
    T* AddLevel(LevelType type, std::wstring name);

    inline WindowsWindow* GetWindow() const { return window_.get(); }
    inline Level* GetLevel() const { return current_level_; }
    inline std::weak_ptr<Actor> GetCamera() const { return camera_; }

private:
    friend bool PreSolve(b2ShapeId shapeIdA, b2ShapeId shapeIdB, b2Manifold* manifold, void* context);
    
    friend class Physics2D;
    friend class Level;
    friend class Actor;
    friend class TilemapComponent;
    friend class CameraComponent;
    friend class PlayerController;
    
    void ProcessCollisionEvents();
    void ProcessTriggerEvents();
    void DestroyActor(Actor* actor);
    void DestroyActors();

    bool PreSolve_Internal(b2ShapeId shapeIdA, b2ShapeId shapeIdB, b2Manifold* manifold);

    inline void SetCamera(const std::shared_ptr<Actor>& kCamera) { camera_ = kCamera; }

    std::shared_ptr<WindowsWindow> window_;
    
    std::shared_ptr<ShapeBatch> shape_batch_;
    
    std::vector<std::shared_ptr<Shape>> shapes_;

    b2WorldId world_id_;
    b2DebugDraw debug_draw_;
    
    b2DebugDrawHelper debug_draw_helper_;
    
    Level* current_level_;
    Level* pending_level_;
    
    std::shared_ptr<Level> levels_[static_cast<MathTypes::uint64>(LevelType::kEnd)];

    std::weak_ptr<Actor> camera_;

    std::queue<std::shared_ptr<Actor>> pending_actors_;
    std::queue<std::shared_ptr<Actor>> pending_destroy_actors_;
};

template <std::derived_from<Actor> T>
T* World::SpawnActor(const std::wstring& kName)
{
    std::shared_ptr<Actor> actor = std::make_shared<T>(kName);
    pending_actors_.push(actor);
    
    actor->InitializeActor();
    return static_cast<T*>(actor.get());
}

template <std::derived_from<Level> T>
T* World::AddLevel(LevelType type, std::wstring name)
{
    levels_[static_cast<MathTypes::uint64>(type)] = std::make_shared<T>(name);
    return static_cast<T*>(levels_[static_cast<MathTypes::uint64>(type)].get());
}
