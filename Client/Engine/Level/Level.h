#pragma once
#include <memory>
#include <string>
#include <vector>

#include "box2d/b2_world_callbacks.h"
#include "box2d/b2_world.h"

#include "DebugDraw.h"
#include "Actor/Actor.h"
#include "Math/Vector2.h"
#include "Graphics/PrimitiveBatch.h"
#include "Listener/ContactListener.h"

enum class EndPlayReason : size_t;

class Level
{
public:
    Level(const std::wstring& kName);
    virtual ~Level() = default;

    virtual void Load() = 0;
    
    virtual void Unload();
    virtual void InitializeActors();
    virtual void PhysicsTick(float delta_time);
    virtual void Interpolate(float alpha);
    virtual void Tick(float delta_time);
    virtual void Render();
    virtual void DestroyActor();

    void AddActor(Actor* actor);

    inline const std::wstring& GetName() const { return name_; }

private:
    std::wstring name_;

    std::vector<std::unique_ptr<Actor>> actors_;

    DebugDraw debug_draw_;
};
