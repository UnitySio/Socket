#pragma once
#include "DebugDraw.h"
#include "Enums.h"
#include "Singleton.h"
#include "box2d/b2_world.h"
#include "Listener/ContactListener.h"

enum class LevelType : size_t;
class Level;

class World : public Singleton<World>
{
public:
    World();
    virtual ~World() override = default;

    void Init();
    void OpenLevel(LevelType type);
    void PhysicsTick(float delta_time);
    void Interpolate(float alpha);
    void Tick(float delta_time);
    void Render();
    void DestroyActor();

    template<std::derived_from<Level> T>
    T* AddLevel(LevelType type, std::wstring name);

    inline Level* GetLevel() const { return current_level_; }

private:
    friend class Level;
    
    std::unique_ptr<b2World> physics_world_;
    
    ContactListener contact_listener_;
    
    DebugDraw debug_draw_;
    
    Level* current_level_;
    std::unique_ptr<Level> levels_[static_cast<size_t>(LevelType::kEnd)];
    
};

template <std::derived_from<Level> T>
T* World::AddLevel(LevelType type, std::wstring name)
{
    levels_[static_cast<size_t>(type)] = std::make_unique<T>(this, name);
    return static_cast<T*>(levels_[static_cast<size_t>(type)].get());
}
