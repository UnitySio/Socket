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
    Scene(const std::wstring& name);
    virtual ~Scene() override = default;

    virtual void BeginContact(b2Contact* contact) override;
    virtual void EndContact(b2Contact* contact) override;

    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) override;

    virtual void BeginPlay();
    virtual void Tick(float delta_time);
    virtual void EndPlay();
    virtual void Render();
    virtual void Destroy();

    void AddActor(Actor* actor);

    inline const std::wstring& GetName() const { return name_; }

    inline b2World* GetWorld() const { return world_.get(); }

    inline void SetScreenPosition(b2Vec2 screen_position) { screen_position_ = screen_position; }
    inline b2Vec2 GetScreenPosition() const { return screen_position_; }

    b2Vec2 GetRenderPosition(b2Vec2 world_position);

private:
    std::wstring name_;

    std::unique_ptr<b2World> world_;

    std::vector<std::unique_ptr<Actor>> actors_;

    DebugDraw debug_draw_;

    b2Vec2 screen_position_;
};
