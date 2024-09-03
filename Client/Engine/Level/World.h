#pragma once
#include <queue>
#include <vector>

#include "Enums.h"
#include "PhysicsDebugDrawHelper.h"
#include "Singleton.h"
#include "box2d/collision.h"
#include "box2d/id.h"
#include "box2d/types.h"

class ShapeBatch;
class Level;
class Actor;
class Shape;
enum class LevelType : MathTypes::uint64;
class WindowsWindow;

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

private:
    friend bool PreSolve(b2ShapeId shapeIdA, b2ShapeId shapeIdB, b2Manifold* manifold, void* context);
    
    friend void DrawPolygon(const b2Vec2* vertices, int vertexCount, b2HexColor color, void* context);
    friend void DrawSolidPolygon(b2Transform transform, const b2Vec2* vertices, int vertexCount, float radius, b2HexColor color, void* context);
    friend void DrawCircle(b2Vec2 center, float radius, b2HexColor color, void* context);
    friend void DrawSolidCircle(b2Transform transform, float radius, b2HexColor color, void* context);
    friend void DrawCapsule(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color, void* context);
    friend void DrawSolidCapsule(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color, void* context);
    friend void DrawSegment(b2Vec2 p1, b2Vec2 p2, b2HexColor color, void* context);
    friend void DrawTransform(b2Transform transform, void* context);
    friend void DrawPoint(b2Vec2 p, float size, b2HexColor color, void* context);
    friend void DrawString(b2Vec2 p, const char* s, void* context);
    
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

    std::shared_ptr<WindowsWindow> window_;
    
    std::shared_ptr<ShapeBatch> shape_batch_;
    
    std::vector<std::shared_ptr<Shape>> shapes_;

    b2WorldId world_id_;
    b2DebugDraw debug_draw_;
    
    PhysicsDebugDrawHelper debug_draw_helper_;
    
    Level* current_level_;
    Level* pending_level_;
    
    std::shared_ptr<Level> levels_[static_cast<MathTypes::uint64>(LevelType::kEnd)];

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
