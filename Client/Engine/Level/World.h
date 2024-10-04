#pragma once
#include <queue>
#include <vector>
#include <rttr/registration>

#include "Enums.h"
#include "Level.h"
#include "PhysicsDebugDrawHelper.h"
#include "Singleton.h"
#include "box2d/id.h"
#include "box2d/types.h"

union Event;
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

    /**
     * Level 내의 특정 타입의 액터들을 가져옵니다.
     * @tparam T 액터 타입
     * @param actors 액터들을 담을 벡터
     */
    template<std::derived_from<Actor> T>
    void GetActors(std::vector<T>& actors);

    /**
     * Level 내의 특정 타입의 액터를 가져옵니다.
     * @tparam T 액터 타입
     * @param kName 액터 이름
     * @return 액터
     */
    template<std::derived_from<Actor> T>
    T* GetActor(const std::wstring& kName);

    template<std::derived_from<Actor> T>
    T* SpawnActor(const std::wstring& kName);

    template<std::derived_from<Level> T>
    T* AddLevel(LevelType type, std::wstring name);

    inline WindowsWindow* GetWindow() const { return window_.get(); }
    inline Level* GetLevel() const { return current_level_; }

private:
    friend void DrawPolygon(const b2Vec2* vertices, int vertexCount, b2HexColor color, void* context);
    friend void DrawSolidPolygon(b2Transform transform, const b2Vec2* vertices, int vertexCount, float radius, b2HexColor color, void* context);
    friend void DrawCircle(b2Vec2 center, float radius, b2HexColor color, void* context);
    friend void DrawSolidCircle(b2Transform transform, float radius, b2HexColor color, void* context);
    friend void DrawSolidCapsule(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color, void* context);
    friend void DrawSegment(b2Vec2 p1, b2Vec2 p2, b2HexColor color, void* context);
    friend void DrawTransform(b2Transform transform, void* context);
    friend void DrawPoint(b2Vec2 p, float size, b2HexColor color, void* context);
    friend void DrawString(b2Vec2 p, const char* s, void* context);

    friend class Core;
    friend class Physics2D;
    friend class Level;
    friend class Actor;
    friend class TilemapComponent;
    friend class CameraComponent;
    friend class PlayerController;

    void OnEvent(const Event& kEvent);
    void ProcessCollisionEvents();
    void ProcessTriggerEvents();
    void ProcessActorActivation();
    void DestroyActor(Actor* actor);
    void DestroyActors();

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
T* World::GetActor(const std::wstring& kName)
{
    rttr::type type = rttr::type::get<T>();
    for (const auto& kActor : current_level_->actors_)
    {
        rttr::type actor_type = rttr::type::get(*kActor);
        if (actor_type.is_derived_from(type) && wcscmp(kActor->GetName().c_str(), kName.c_str()) == 0)
        {
            return static_cast<T*>(kActor.get());
        }
    }
    
    return nullptr;
}

template <std::derived_from<Actor> T>
void World::GetActors(std::vector<T>& actors)
{
    rttr::type type = rttr::type::get<T>();
    for (const auto& kActor : current_level_->actors_)
    {
        rttr::type actor_type = rttr::type::get(*kActor);
        if (actor_type.is_derived_from(type))
        {
            actors.push_back(static_cast<T*>(kActor.get()));
        }
    }
}

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
