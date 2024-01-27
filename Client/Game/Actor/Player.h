﻿#pragma once
#include "../../Engine/Actor/Actor.h"

class Player : public Actor
{
public:
    Player(class b2World* world, const std::wstring& name);
    virtual ~Player() override = default;

    virtual void Tick(float delta_time) override;

private:
    bool is_ground_;
    
};
