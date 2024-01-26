#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Windows.h"
#include "box2d/b2_world_callbacks.h"
#include "box2d/b2_world.h"

#include "../DebugDraw.h"

class Actor;

class Scene : public b2ContactListener
{
public:
    Scene();
    virtual ~Scene() override = default;

    virtual void BeginContact(b2Contact* contact) override;
    virtual void EndContact(b2Contact* contact) override;

    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;

    virtual void Begin();
    virtual void Tick(float deltaTime);
    virtual void Render();
    virtual void Destroy();

    virtual inline void End() {};

    void AddActor(Actor* actor);

    inline void SetName(const std::wstring name) { name_ = name; }
    inline const std::wstring GetName() const { return name_; }

    inline b2World* GetWorld() const { return world_.get(); }

private:
    std::wstring name_;

    std::unique_ptr<b2World> world_;

    std::vector<std::unique_ptr<Actor>> actors_;

    DebugDraw debug_draw_;
};
