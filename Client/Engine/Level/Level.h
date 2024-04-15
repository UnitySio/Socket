#pragma once
#include <memory>
#include <string>
#include <vector>

#include "box2d/b2_world_callbacks.h"
#include "box2d/b2_world.h"

#include "DebugDraw.h"
#include "Math/Vector.h"
#include "Graphics/PrimitiveBatch.h"
#include "Listener/ContactListener.h"

enum class EndPlayReason : size_t;
class Actor;

class Level : public b2ContactListener
{
public:
    Level(const std::wstring& kName);
    virtual ~Level() override = default;
    
    virtual void InitializeActors();
    virtual void PhysicsTick(float delta_time);
    virtual void Interpolate(float alpha);
    virtual void Tick(float delta_time);
    virtual void EndPlay(EndPlayReason type);
    virtual void Render();
    virtual void DestroyActor();

    void AddActor(Actor* actor);

    inline const std::wstring& GetName() const { return name_; }

    inline b2World* GetWorld() const { return world_.get(); }

    inline void SetScreenPosition(Math::Vector screen_position) { screen_position_ = screen_position; }
    inline Math::Vector GetScreenPosition() const { return screen_position_; }

    b2Vec2 GetRenderPosition(b2Vec2 world_position);
    b2Vec2 GetWorldPosition(b2Vec2 render_position);

    inline PrimitiveBatch* GetPrimitiveBatch() const { return primitive_batch_.get(); }

private:
    std::wstring name_;

    std::unique_ptr<b2World> world_;

    std::vector<std::unique_ptr<Actor>> actors_;

    DebugDraw debug_draw_;

    Math::Vector screen_position_;

    ContactListener contact_listener_;

    std::unique_ptr<PrimitiveBatch> primitive_batch_;
};
