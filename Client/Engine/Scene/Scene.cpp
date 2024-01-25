#include "Scene.h"

#include "box2d/b2_math.h"
#include "box2d/b2_world.h"

#include "../Actor/Actor.h"
#include "box2d/b2_contact.h"

Scene::Scene()
{
    b2Vec2 gravity(0.0f, 9.81f);
    world_ = std::make_unique<b2World>(gravity);
    world_->SetContactListener(this);
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
    for (auto& actor : actors_)
    {
        if (!actor->is_active_ || actor->is_destroy_) continue;
        actor->Tick(deltaTime);
    }
    
    world_->Step(deltaTime, 8, 3);
}

void Scene::Render()
{
    for (auto& actor : actors_)
    {
        if (!actor->is_active_ || actor->is_destroy_) continue;
        actor->Render();
    }
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

void Scene::AddActor(std::shared_ptr<Actor> actor)
{
    actors_.push_back(actor);
}
