#pragma once
#include <vector>

#include "box2d/b2_world_callbacks.h"

class ContactListener : public b2ContactListener
{
public:
    ContactListener();
    virtual ~ContactListener() override = default;
    
    virtual void BeginContact(b2Contact* contact) override;
    virtual void EndContact(b2Contact* contact) override;
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) override;

    void OnTriggerStay(b2Contact* contact);
    void Tick();

private:
    std::vector<b2Contact*> triggered_contacts_;
    
};
