#include "pch.h"
#include "ContactListener.h"

#include "box2d/b2_contact.h"
#include "Actor/Actor.h"

ContactListener::ContactListener() :
    triggered_contacts_()
{
}

void ContactListener::BeginContact(b2Contact* contact)
{
    b2Fixture* fixture_a = contact->GetFixtureA();
    b2Fixture* fixture_b = contact->GetFixtureB();

    b2Body* body_a = fixture_a->GetBody();
    b2Body* body_b = fixture_b->GetBody();

    Actor* actor_a = reinterpret_cast<Actor*>(body_a->GetUserData().pointer);
    Actor* actor_b = reinterpret_cast<Actor*>(body_b->GetUserData().pointer);

    if (!actor_a || !actor_b) return;
    if (fixture_a->IsSensor() || fixture_b->IsSensor())
    {
        actor_a->OnTriggerEnter(actor_b);
        actor_b->OnTriggerEnter(actor_a);

        triggered_contacts_.push_back(contact);
        return;
    }

    actor_a->OnCollisionEnter(actor_b);
    actor_b->OnCollisionEnter(actor_a);
}

void ContactListener::EndContact(b2Contact* contact)
{
    b2Fixture* fixture_a = contact->GetFixtureA();
    b2Fixture* fixture_b = contact->GetFixtureB();

    b2Body* body_a = fixture_a->GetBody();
    b2Body* body_b = fixture_b->GetBody();

    Actor* actor_a = reinterpret_cast<Actor*>(body_a->GetUserData().pointer);
    Actor* actor_b = reinterpret_cast<Actor*>(body_b->GetUserData().pointer);

    if (!actor_a || !actor_b) return;
    if (fixture_a->IsSensor() || fixture_b->IsSensor())
    {
        actor_a->OnTriggerExit(actor_b);
        actor_b->OnTriggerExit(actor_a);

        std::erase(triggered_contacts_, contact);
        return;
    }

    actor_a->OnCollisionExit(actor_b);
    actor_b->OnCollisionExit(actor_a);
}

void ContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
    b2Fixture* fixture_a = contact->GetFixtureA();
    b2Fixture* fixture_b = contact->GetFixtureB();

    b2Body* body_a = fixture_a->GetBody();
    b2Body* body_b = fixture_b->GetBody();

    Actor* actor_a = reinterpret_cast<Actor*>(body_a->GetUserData().pointer);
    Actor* actor_b = reinterpret_cast<Actor*>(body_b->GetUserData().pointer);

    if (!actor_a || !actor_b) return;

    actor_a->OnCollisionStay(actor_b);
    actor_b->OnCollisionStay(actor_a);
}

void ContactListener::OnTriggerStay(b2Contact* contact)
{
    b2Fixture* fixture_a = contact->GetFixtureA();
    b2Fixture* fixture_b = contact->GetFixtureB();

    b2Body* body_a = fixture_a->GetBody();
    b2Body* body_b = fixture_b->GetBody();

    Actor* actor_a = reinterpret_cast<Actor*>(body_a->GetUserData().pointer);
    Actor* actor_b = reinterpret_cast<Actor*>(body_b->GetUserData().pointer);

    if (!actor_a || !actor_b) return;
    if (body_a->IsAwake()) actor_a->OnTriggerStay(actor_b);
    if (body_b->IsAwake()) actor_b->OnTriggerStay(actor_a);
}

void ContactListener::Tick()
{
    for (const auto& contact : triggered_contacts_)
    {
        OnTriggerStay(contact);
    }
}
