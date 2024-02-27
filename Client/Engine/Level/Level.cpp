#include "Level.h"

#include <iostream>

#include "box2d/b2_math.h"
#include "box2d/b2_world.h"

#include "../Actor/Actor.h"
#include "box2d/b2_contact.h"

Level::Level(const std::wstring& kName) :
    world_(nullptr),
    actors_(),
    debug_draw_(),
    screen_position_(Vector::Zero()),
    triggered_contacts_()
{
    name_ = kName;

    b2Vec2 gravity(0.f, 9.81f * 100.f);
    world_ = std::make_unique<b2World>(gravity);
    world_->SetContactListener(this);

    uint32 flags = 0;
    flags += b2Draw::e_shapeBit;
    flags += b2Draw::e_jointBit;
    flags += b2Draw::e_aabbBit;
    flags += b2Draw::e_pairBit;
    flags += b2Draw::e_centerOfMassBit;
    debug_draw_.SetFlags(flags);

    world_->SetDebugDraw(&debug_draw_);
}

void Level::BeginContact(b2Contact* contact)
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

void Level::EndContact(b2Contact* contact)
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

void Level::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
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

void Level::OnTriggerStay(b2Contact* contact)
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

void Level::BeginPlay()
{
    for (auto& actor : actors_)
    {
        actor->BeginPlay();
    }
}

void Level::PhysicsTick(float delta_time)
{
    for (const auto& actor : actors_)
    {
        if (!actor->is_active_ || actor->is_destroy_) continue;

        b2Vec2 position = actor->body_->GetPosition();
        actor->previous_location_ = {position.x, position.y};
        actor->previous_angle_ = actor->body_->GetAngle();
    }

    world_->Step(delta_time, 8, 3);

    for (const auto& contact : triggered_contacts_)
    {
        OnTriggerStay(contact);
    }

    for (auto& actor : actors_)
    {
        if (!actor->is_active_ || actor->is_destroy_) continue;
        actor->PhysicsTick(delta_time);
    }
}

void Level::Interpolate(float alpha)
{
    for (b2Body* body = world_->GetBodyList(); body; body = body->GetNext())
    {
        if (body->GetType() == b2_staticBody) continue;

        const Actor* actor = reinterpret_cast<Actor*>(body->GetUserData().pointer);
        if (!actor) continue;

        const b2Vec2 position = body->GetPosition();
        const b2Vec2 previous_position = {actor->previous_location_.x, actor->previous_location_.y};

        b2Vec2 interpolated_position = {
            position.x * alpha + previous_position.x * (1.f - alpha),
            position.y * alpha + previous_position.y * (1.f - alpha)
        };

        const float interpolated_angle = body->GetAngle() * alpha + actor->previous_angle_ * (1.f - alpha);

        body->SetTransform(interpolated_position, interpolated_angle);
    }
}

void Level::Tick(float delta_time)
{
    for (auto& actor : actors_)
    {
        if (!actor->is_active_ || actor->is_destroy_) continue;
        actor->Tick(delta_time);
    }
}

void Level::EndPlay()
{
    for (auto& actor : actors_)
    {
        actor->EndPlay();
    }
}

void Level::Render()
{
    world_->DebugDraw();

    for (auto& actor : actors_)
    {
        if (!actor->is_active_ || actor->is_destroy_) continue;
        actor->Render();
    }
}

void Level::Destroy()
{
    for (auto iter = actors_.begin(); iter != actors_.end();)
    {
        if ((*iter)->is_destroy_)
        {
            (*iter)->EndPlay();
            iter = actors_.erase(iter);
        }
        else
        {
            ++iter;
        }
    }
}

void Level::AddActor(Actor* actor)
{
    actors_.push_back(std::unique_ptr<Actor>(actor));
}

b2Vec2 Level::GetRenderPosition(b2Vec2 world_position)
{
    const b2Vec2 screen_position = {screen_position_.x, screen_position_.y};
    return world_position - screen_position;
}
