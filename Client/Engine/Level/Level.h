#pragma once
#include <memory>
#include <string>
#include <vector>

#include "DebugDraw.h"
#include "Actor/Actor.h"

enum class EndPlayReason : size_t;

class World;
class Level
{
public:
    Level(World* world, const std::wstring& kName);
    virtual ~Level() = default;

    virtual void Load() = 0;
    
    virtual void Unload(EndPlayReason type);
    virtual void InitializeActors();
    virtual void PhysicsTick(float delta_time);
    virtual void Tick(float delta_time);
    virtual void Render(float alpha);
    virtual void DestroyActor();

    void AddActor(Actor* actor);

    inline World* GetWorld() const { return world_; }
    inline const std::wstring& GetName() const { return name_; }

private:
    World* world_;
    std::wstring name_;

    std::vector<std::shared_ptr<Actor>> actors_;

    DebugDraw debug_draw_;
};
