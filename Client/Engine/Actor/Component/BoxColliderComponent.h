#pragma once
#include "ColliderComponent.h"

class BoxColliderComponent : public ColliderComponent
{
public:
    BoxColliderComponent(Actor* owner, const std::wstring& kName);
    virtual ~BoxColliderComponent() override = default;

    virtual void SetOffset(const Vector& kOffset) override;

    void SetSize(Vector size);

private:
    void SetBox();
    
    Vector size_;
    
};
