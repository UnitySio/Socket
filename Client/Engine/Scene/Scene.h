#pragma once
#include <memory>
#include <vector>

#include "Windows.h"
#include "box2d/b2_world_callbacks.h"
#include "box2d/b2_world.h"

class Scene : public b2ContactListener
{
public:
    Scene();
    virtual ~Scene() = default;

    virtual void BeginContact(b2Contact* contact) final;
    virtual void EndContact(b2Contact* contact) final;

    virtual void PreSolve(b2Contact* contact, const b2Manifold* oldManifold) final;

    virtual void Begin();
    virtual void Tick(float deltaTime);
    virtual void Render();
    virtual void Destroy();
    
    virtual inline void End() {};

    void AddActor(std::shared_ptr<class Actor> actor);

    inline void SetName(const char* name) { strcpy_s(name_, name); }
    inline const char* GetName() const { return name_; }

    inline b2World* GetWorld() const { return world_.get(); }

private:
    char name_[256];

    std::unique_ptr<b2World> world_;

    std::vector<std::shared_ptr<class Actor>> actors_;
    
};
