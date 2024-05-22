#pragma once
#include "Level/Level.h"

class MainMap : public Level
{
public:
    MainMap(const std::wstring& kName);
    virtual ~MainMap() override = default;
    virtual void Tick(float delta_time) override;
    virtual void Load() override;
    

private:
    float timer = 0.0f;
    Actor* pawn2;
    Actor* pawn3;
    Actor* pawn;

    bool flag;
};
