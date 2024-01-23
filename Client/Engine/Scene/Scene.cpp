#include "Scene.h"

#include "box2d/b2_math.h"
#include "box2d/b2_world.h"

#include "../Actor/Actor.h"

Scene::Scene()
{
    b2Vec2 gravity(0.0f, 9.81f * 200.f);
    world_ = std::make_unique<b2World>(gravity);
    world_->SetContactListener(this);
}

void Scene::BeginContact(b2Contact* contact)
{
    b2ContactListener::BeginContact(contact);
}

void Scene::EndContact(b2Contact* contact)
{
    b2ContactListener::EndContact(contact);
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
        actor->Tick(deltaTime);
    }
}

void Scene::Render()
{
    for (auto& actor : actors_)
    {
        actor->Render();
    }
}

void Scene::AddActor(std::shared_ptr<Actor> actor)
{
    actors_.push_back(actor);
}
