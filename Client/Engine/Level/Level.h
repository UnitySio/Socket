#pragma once
#include <memory>
#include <string>
#include <vector>

#include "DebugDraw.h"
#include "Actor/Actor.h"

enum class EndPlayReason : size_t;

class Level
{
public:
    Level(const std::wstring& kName);
    virtual ~Level() = default;

    virtual void Load() = 0;
    
    virtual void Unload(EndPlayReason type);
    virtual void InitializeActors();
    virtual void PhysicsTick(float delta_time);
    virtual void Tick(float delta_time);
    virtual void PostTick(float delta_time);
    virtual void Render(float alpha);
    virtual void DestroyActor();

    void AddActor(const SHARED_PTR<Actor>& actor);

    inline const std::wstring& GetName() const { return name_; }

private:
    std::wstring name_;

    std::vector<SHARED_PTR<Actor>> actors_;

    DebugDraw debug_draw_;
};
