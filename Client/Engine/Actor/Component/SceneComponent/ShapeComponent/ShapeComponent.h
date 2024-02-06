#pragma once
#include "../SceneComponent.h"

class b2Body;

class ShapeComponent : public SceneComponent
{
public:
    ShapeComponent(Actor* owner, const std::wstring& kName);
    virtual ~ShapeComponent() override = default;

    virtual void EndPlay() override;

    // 만약 부모에 붙였을 때, 부모의 바디를 찾아 하나로 통합한다.
    virtual void SetupAttachment(SceneComponent* parent) override;

protected:
    class b2Fixture* fixture_;

private:
    void SetBodyNullptr(const std::vector<SceneComponent*>& kChildren);
    
};
