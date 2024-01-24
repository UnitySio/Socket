#include "Actor.h"

#include "box2d/b2_body.h"
#include "box2d/b2_world.h"

Actor::Actor(b2World* world)
{
    b2BodyDef body_def;
    body_def.userData.pointer = reinterpret_cast<uintptr_t>(this);
    body_def.position.Set(0.0f, 0.0f);

    body_ = world->CreateBody(&body_def);
}

Actor::Actor(const Actor& kOrigin)
{
    strcpy_s(name_, kOrigin.name_);

    // 추후 구현
}
