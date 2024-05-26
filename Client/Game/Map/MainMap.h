#pragma once
#include "Level/Level.h"
#include <functional>

class MainMap : public Level
{
public:
    MainMap(const std::wstring& kName);
    virtual ~MainMap() override = default;
    virtual void Tick(float delta_time) override;
    virtual void Load() override;
    virtual void PhysicsTick(float dt) override;


#pragma region Joint
    void ReserveDestroyJoint(b2Joint* joint);
    void ReserveCreateJoint(std::function<void()>&& func);
#pragma endregion

private:

#pragma region Joint
    void DestroyReservedJoint();
    void CreateReservedJoint();
    float timer = 0.0f;
    std::vector<b2Joint*> destroyContainer_;
    std::vector<std::function<void()>> createContainer_;
    bool flag1;
    bool flag2;
#pragma endregion

    Actor* pawn2;
    Actor* pawn3;
    Actor* pawn;
    
    
};
