#include "Level.h"

#include "box2d/b2_math.h"
#include "box2d/b2_world.h"

#include "../Actor/Actor.h"
#include "box2d/b2_contact.h"

Level::Level(const std::wstring& kName) :
    world_(nullptr),
    actors_(),
    debug_draw_(),
    screen_position_(Vector::Zero())
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
    // b2Fixture* fixture_a = contact->GetFixtureA();
    // b2Fixture* fixture_b = contact->GetFixtureB();
    //
    // b2Body* body_a = fixture_a->GetBody();
    // b2Body* body_b = fixture_b->GetBody();
    //
    // Actor* actor_a = reinterpret_cast<Actor*>(body_a->GetUserData().pointer);
    // Actor* actor_b = reinterpret_cast<Actor*>(body_b->GetUserData().pointer);
    //
    // if (!actor_a || !actor_b) return;
    // if (fixture_a->IsSensor() || fixture_b->IsSensor())
    // {
    //     actor_a->OnTriggerEnter(actor_b);
    //     actor_b->OnTriggerEnter(actor_a);
    //     return;
    // }
    //
    // actor_a->OnCollisionEnter(actor_b);
    // actor_b->OnCollisionEnter(actor_a);
}

void Level::EndContact(b2Contact* contact)
{
    // b2Fixture* fixture_a = contact->GetFixtureA();
    // b2Fixture* fixture_b = contact->GetFixtureB();
    //
    // b2Body* body_a = fixture_a->GetBody();
    // b2Body* body_b = fixture_b->GetBody();
    //
    // Actor* actor_a = reinterpret_cast<Actor*>(body_a->GetUserData().pointer);
    // Actor* actor_b = reinterpret_cast<Actor*>(body_b->GetUserData().pointer);
    //
    // if (!actor_a || !actor_b) return;
    // if (fixture_a->IsSensor() || fixture_b->IsSensor())
    // {
    //     actor_a->OnTriggerExit(actor_b);
    //     actor_b->OnTriggerExit(actor_a);
    //     return;
    // }
    //
    // actor_a->OnCollisionExit(actor_b);
    // actor_b->OnCollisionExit(actor_a);
}

void Level::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
    // b2Fixture* fixture_a = contact->GetFixtureA();
    // b2Fixture* fixture_b = contact->GetFixtureB();
    //
    // b2Body* body_a = fixture_a->GetBody();
    // b2Body* body_b = fixture_b->GetBody();
    //
    // Actor* actor_a = reinterpret_cast<Actor*>(body_a->GetUserData().pointer);
    // Actor* actor_b = reinterpret_cast<Actor*>(body_b->GetUserData().pointer);
    //
    // if (!actor_a || !actor_b) return;
    // if (fixture_a->IsSensor() || fixture_b->IsSensor())
    // {
    //     actor_a->OnTriggerStay(actor_b);
    //     actor_b->OnTriggerStay(actor_a);
    //     return;
    // }
    //
    // actor_a->OnCollisionStay(actor_b);
    // actor_b->OnCollisionStay(actor_a);
}

void Level::BeginPlay()
{
    for (auto& actor : actors_)
    {
        actor->BeginPlay();
    }
}

void Level::Tick(float delta_time)
{
    world_->Step(delta_time, 8, 3);
    
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
    for (auto& actor : actors_)
    {
        if (!actor->is_active_ || actor->is_destroy_) continue;
        actor->Render();
    }
    
    world_->DebugDraw();
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
