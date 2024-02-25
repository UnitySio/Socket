#pragma once
#include <memory>
#include <string>
#include <vector>

#include "box2d/b2_world_callbacks.h"
#include "box2d/b2_world.h"

#include "../DebugDraw.h"
#include "../Vector.h"

class Actor;

class Level : public b2ContactListener
{
public:
    Level(const std::wstring& kName);
    virtual ~Level() override = default;

    virtual void BeginContact(b2Contact* contact) override;
    virtual void EndContact(b2Contact* contact) override;

    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

    void OnTriggerStay(b2Contact* contact);
    
    virtual void BeginPlay();
    virtual void PhysicsTick(float delta_time);
    virtual void Tick(float delta_time);
    virtual void EndPlay();
    virtual void Render();
    virtual void Destroy();

    template<std::derived_from<Actor> T>
    T* AddActor(std::wstring name);

    inline const std::wstring& GetName() const { return name_; }

    inline b2World* GetWorld() const { return world_.get(); }

    inline void SetScreenPosition(Vector screen_position) { screen_position_ = screen_position; }
    inline Vector GetScreenPosition() const { return screen_position_; }

    b2Vec2 GetRenderPosition(b2Vec2 world_position);

private:
    std::wstring name_;

    std::unique_ptr<b2World> world_;

    std::vector<std::unique_ptr<Actor>> actors_;

    DebugDraw debug_draw_;

    Vector screen_position_;

    std::vector<b2Contact*> triggered_contacts_;
};

template <std::derived_from<Actor> T>
T* Level::AddActor(std::wstring name)
{
    actors_.push_back(std::make_unique<T>(world_.get(), name));
    return static_cast<T*>(actors_.back().get());
}
