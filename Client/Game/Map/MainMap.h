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

    void ReserveDestroyJoint(b2Joint* joint);
    void ReserveCreateJoint(b2Joint* joint, b2JointDef* jointDef, std::function<void(b2Joint*, b2JointDef*)> func);

private:
    void DestroyReservedJoint();
    void CreateReservedJoint();

    float timer = 0.0f;
    Actor* pawn2;
    Actor* pawn3;
    Actor* pawn;
    
    std::vector<b2Joint*> destroyContainer_;

    std::vector<std::tuple<b2Joint*, b2JointDef*, std::function<void(b2Joint*, b2JointDef*)>>> createContainer_;

    bool flag;
};
