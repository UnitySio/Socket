#pragma once
#include "ActorComponent.h"
#include "box2d/id.h"
#include "Math/Bounds.h"
#include "Math/Vector2.h"

struct PhysicsMaterial2D
{
    float friction = .3f;
    float bounciness = 0.f;
};

class ColliderComponent : public ActorComponent
{
    SHADER_CLASS_HELPER(ColliderComponent)
    
public:
    ColliderComponent(Actor* owner, const std::wstring& kName);
    virtual ~ColliderComponent() override = default;

    virtual void SetOffset(const Math::Vector2& kOffset);
    virtual void SetTrigger(bool is_trigger);

    void SetMaterial(const PhysicsMaterial2D& kMaterial);
    void SetPreSolve(bool is_pre_solve);

    const Bounds& GetBounds();

    inline bool SetOneWayPlatform(bool is_one_way_platform) { return is_one_way_platform_ = is_one_way_platform; }

protected:
    friend class World;
    
    b2ShapeId shape_id_;

    Math::Vector2 offset_;

    PhysicsMaterial2D material_;

    bool is_one_way_platform_;

private:
    virtual void SetShape();
    
};
