#include "Scene.h"

#include "box2d/b2_math.h"
#include "box2d/b2_world.h"

#include "../Actor/Actor.h"
#include "box2d/b2_contact.h"

Scene::Scene() :
    world_(nullptr),
    actors_(),
    debug_draw_()
{
    b2Vec2 gravity(0.0f, 9.81f * 100.0f);
    world_ = std::make_unique<b2World>(gravity);
    world_->SetContactListener(this);
    
    // uint32 flags = 0;
    // flags += b2Draw::e_shapeBit;
    // flags += b2Draw::e_jointBit;
    // flags += b2Draw::e_aabbBit;
    // flags += b2Draw::e_pairBit;
    // flags += b2Draw::e_centerOfMassBit;
    // debug_draw_.SetFlags(flags);

    world_->SetDebugDraw(&debug_draw_);
}

void Scene::BeginContact(b2Contact* contact)
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
        actor_a->OnTriggerBegin(actor_b);
        actor_b->OnTriggerBegin(actor_a);
        return;
    }

    actor_a->OnCollisionBegin(actor_b);
    actor_b->OnCollisionBegin(actor_a);
}

void Scene::EndContact(b2Contact* contact)
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
        actor_a->OnTriggerEnd(actor_b);
        actor_b->OnTriggerEnd(actor_a);
        return;
    }

    actor_a->OnCollisionEnd(actor_b);
    actor_b->OnCollisionEnd(actor_a);
}

void Scene::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
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
        actor_a->OnTrigger(actor_b);
        actor_b->OnTrigger(actor_a);
        return;
    }

    actor_a->OnCollision(actor_b);
    actor_b->OnCollision(actor_a);
}

void Scene::Begin()
{
    for (auto& actor : actors_)
    {
        actor->Begin();
    }
}

void Scene::Tick(float deltaTime)
{
    world_->Step(deltaTime, 8, 3);
    
    for (auto& actor : actors_)
    {
        if (!actor->is_active_ || actor->is_destroy_) continue;
        actor->Tick(deltaTime);
    }
}

void Scene::Render()
{
    for (auto& actor : actors_)
    {
        if (!actor->is_active_ || actor->is_destroy_) continue;
        actor->Render();
    }
    
    world_->DebugDraw();
}

void Scene::Destroy()
{
    for (auto iter = actors_.begin(); iter != actors_.end();)
    {
        if ((*iter)->is_destroy_)
        {
            iter = actors_.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

void Scene::AddActor(Actor* actor)
{
    actors_.push_back(std::unique_ptr<Actor>(actor));
}
