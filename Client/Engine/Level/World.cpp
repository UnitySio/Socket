#include "pch.h"
#include "World.h"

#include "DebugDrawHelper.h"
#include "Actor/Camera.h"
#include "Actor/Component/ColliderComponent.h"
#include "box2d/box2d.h"
#include "Map/MainMap.h"
#include "Map/MainMenu.h"
#include "Map/SplashMap.h"
#include "Time/TimerManager.h"
#include "UI/Canvas.h"
#include "Windows/WindowsWindow.h"
#include "Windows/DX/Shape.h"
#include "Windows/DX/ShapeBatch.h"

bool PreSolve(b2ShapeId shapeIdA, b2ShapeId shapeIdB, b2Manifold* manifold, void* context);
void DrawPolygon(const b2Vec2* vertices, int vertexCount, b2HexColor color, void* context);
void DrawSolidPolygon(b2Transform transform, const b2Vec2* vertices, int vertexCount, float radius, b2HexColor color, void* context);
void DrawCircle(b2Vec2 center, float radius, b2HexColor color, void* context);
void DrawSolidCircle(b2Transform transform, float radius, b2HexColor color, void* context);
void DrawCapsule(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color, void* context);
void DrawSolidCapsule(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color, void* context);
void DrawSegment(b2Vec2 p1, b2Vec2 p2, b2HexColor color, void* context);
void DrawTransform(b2Transform transform, void* context);
void DrawPoint(b2Vec2 p, float size, b2HexColor color, void* context);
void DrawString(b2Vec2 p, const char* s, void* context);

World::World() :
    window_(nullptr),
    shape_batch_(nullptr),
    shapes_(),
    current_level_(nullptr),
    pending_level_(nullptr),
    levels_(),
    pending_actors_()
{
    shape_batch_ = std::make_shared<ShapeBatch>();
    shape_batch_->Init();
    
    b2Vec2 gravity(0.f, -9.81f);
    b2WorldDef world_def = b2DefaultWorldDef();
    world_def.gravity = gravity;

    world_id_ = b2CreateWorld(&world_def);

    b2World_SetPreSolveCallback(world_id_, PreSolve, this);

    b2AABB bounds = {
        {-FLT_MAX, -FLT_MAX},
        {FLT_MAX, FLT_MAX},
    };

    debug_draw_ = {
        DrawPolygon,
        DrawSolidPolygon,
        DrawCircle,
        DrawSolidCircle,
        DrawCapsule,
        DrawSolidCapsule,
        DrawSegment,
        DrawTransform,
        DrawPoint,
        DrawString,
        bounds,
        false,
        true,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        false,
        this
    };
}

World::~World()
{
    b2DestroyWorld(world_id_);
    world_id_ = b2_nullWorldId;
}

void World::Init(const std::shared_ptr<WindowsWindow>& kWindow)
{
    window_ = kWindow;
    
    AddLevel<SplashMap>(LevelType::kSplash, L"Splash");
    AddLevel<MainMenu>(LevelType::kMainMenu, L"Main Menu");
    AddLevel<MainMap>(LevelType::kDefault, L"Unknown");
    
    OpenLevel(LevelType::kSplash);
}

void World::OpenLevel(LevelType type)
{
    pending_level_ = levels_[static_cast<MathTypes::uint64>(type)].get();
}

void World::PhysicsTick(float delta_time)
{
    b2World_Step(world_id_, delta_time, 4);
    
    if (current_level_)
    {
        ProcessCollisionEvents();
        ProcessTriggerEvents();
        
        current_level_->PhysicsTick(delta_time);
        DestroyActors();
    }
}

void World::Tick(float delta_time)
{
    TimerManager::Get()->Tick(delta_time);
    
    if (current_level_)
    {
        current_level_->Tick(delta_time);
        DestroyActors();
    }
}

void World::PostTick(float delta_time)
{
    if (current_level_)
    {
        current_level_->PostTick(delta_time);
        DestroyActors();
    }
}

void World::Render(float alpha)
{
    if (current_level_)
    {
        current_level_->Render(alpha);
    }
    
    b2World_Draw(world_id_, &debug_draw_);
    debug_draw_helper_.Clear();

    DebugDrawHelper::Get()->Clear();

    std::vector<std::shared_ptr<Shape>> shapes;

    if (Camera* camera = Camera::Get())
    {
        Bounds bounds = camera->GetBounds();
        for (const auto& kShape : shapes_)
        {
            if (Bounds::Contains(bounds, kShape->GetBounds()))
            {
                shapes.push_back(kShape);
            }
        }
    }
    
    std::ranges::sort(shapes, Shape::CompareZOrder);
    
    shapes_.clear();
    
    shape_batch_->DrawShapes(window_, shapes);
}

void World::AddShape(const std::shared_ptr<Shape>& kShape)
{
    shapes_.push_back(kShape);
}

void World::TransitionLevel()
{
    if (!pending_level_) return;
    
    if (current_level_)
    {
        current_level_->Unload(EndPlayReason::kLevelTransition);
        Canvas::Get()->Clear();
    }

    current_level_ = pending_level_;
    pending_level_ = nullptr;

    current_level_->AddActor<Camera>(L"Main Camera");
    
    current_level_->Load();
    current_level_->InitializeActors();
    DestroyActors();
    SpawnActors();
    
    SetWindowText(window_->GetHWnd(), current_level_->GetName().c_str());
}

void World::SpawnActors()
{
    while (!pending_actors_.empty())
    {
        std::shared_ptr<Actor> actor = pending_actors_.front();
        current_level_->actors_.push_back(actor);
        actor->BeginPlay();
        
        pending_actors_.pop();
    }
}

void World::ProcessCollisionEvents()
{
    b2ContactEvents events = b2World_GetContactEvents(World::Get()->world_id_);
    for (MathTypes::uint32 i = 0; i < events.beginCount; ++i)
    {
        b2ContactBeginTouchEvent event = events.beginEvents[i];
        b2BodyId body_id_a = b2Shape_GetBody(event.shapeIdA);
        b2BodyId body_id_b = b2Shape_GetBody(event.shapeIdB);

        Actor* actor_a = static_cast<Actor*>(b2Body_GetUserData(body_id_a));
        Actor* actor_b = static_cast<Actor*>(b2Body_GetUserData(body_id_b));

        if (!actor_a || !actor_b) continue;
        
        actor_a->OnCollisionEnter(actor_b);
        actor_b->OnCollisionEnter(actor_a);
    }

    for (MathTypes::uint32 i = 0; i < events.endCount; ++i)
    {
        b2ContactEndTouchEvent event = events.endEvents[i];
        b2BodyId body_id_a = b2Shape_GetBody(event.shapeIdA);
        b2BodyId body_id_b = b2Shape_GetBody(event.shapeIdB);

        Actor* actor_a = static_cast<Actor*>(b2Body_GetUserData(body_id_a));
        Actor* actor_b = static_cast<Actor*>(b2Body_GetUserData(body_id_b));

        if (!actor_a || !actor_b) continue;
        
        actor_a->OnCollisionExit(actor_b);
        actor_b->OnCollisionExit(actor_a);
    }
}

void World::ProcessTriggerEvents()
{
    b2SensorEvents events = b2World_GetSensorEvents(World::Get()->world_id_);
    for (MathTypes::uint32 i = 0; i < events.beginCount; ++i)
    {
        b2SensorBeginTouchEvent event = events.beginEvents[i];
        b2BodyId body_id_a = b2Shape_GetBody(event.sensorShapeId);
        b2BodyId body_id_b = b2Shape_GetBody(event.visitorShapeId);
        
        Actor* actor_a = static_cast<Actor*>(b2Body_GetUserData(body_id_a));
        Actor* actor_b = static_cast<Actor*>(b2Body_GetUserData(body_id_b));
        
        if (!actor_a || !actor_b) continue;
        actor_a->OnTriggerEnter(actor_b);
        actor_b->OnTriggerEnter(actor_a);
    }
    
    for (MathTypes::uint32 i = 0; i < events.endCount; ++i)
    {
        b2SensorEndTouchEvent event = events.endEvents[i];
        b2BodyId body_id_a = b2Shape_GetBody(event.sensorShapeId);
        b2BodyId body_id_b = b2Shape_GetBody(event.visitorShapeId);
        
        Actor* actor_a = static_cast<Actor*>(b2Body_GetUserData(body_id_a));
        Actor* actor_b = static_cast<Actor*>(b2Body_GetUserData(body_id_b));
        
        if (!actor_a || !actor_b) continue;
        actor_a->OnTriggerExit(actor_b);
        actor_b->OnTriggerExit(actor_a);
    }
}

void World::DestroyActor(Actor* actor)
{
    actor->is_pending_destroy_ = true;
    
    std::shared_ptr<Actor> shared_actor = actor->GetSharedThis();
    pending_destroy_actors_.push(shared_actor);
}

void World::DestroyActors()
{
    while (!pending_destroy_actors_.empty())
    {
        std::shared_ptr<Actor> actor = pending_destroy_actors_.front();
        actor->Destroyed();
        
        std::erase(current_level_->actors_, actor);
        pending_destroy_actors_.pop();
    }
}

bool World::PreSolve_Internal(b2ShapeId shapeIdA, b2ShapeId shapeIdB, b2Manifold* manifold)
{
    ColliderComponent* collider_a = static_cast<ColliderComponent*>(b2Shape_GetUserData(shapeIdA));
    ColliderComponent* collider_b = static_cast<ColliderComponent*>(b2Shape_GetUserData(shapeIdB));

    if (!collider_a || !collider_b) return true;

    float sign = 0.f;
    if (collider_a->is_one_way_platform_)
    {
        sign = 1.f;
    }
    else if (collider_b->is_one_way_platform_)
    {
        sign = -1.f;
    }
    else return true;

    b2Vec2 normal = manifold->normal;
    if (sign * normal.y > .95f) return true;

    float separation = 0.f;
    for (int i = 0; i < manifold->pointCount; ++i)
    {
        float s = manifold->points[i].separation;
        separation = separation < s ? separation : s;
    }

    if (separation > .1f * .5f) return true;
    
    return false;
}

bool PreSolve(b2ShapeId shapeIdA, b2ShapeId shapeIdB, b2Manifold* manifold, void* context)
{
    return static_cast<World*>(context)->PreSolve_Internal(shapeIdA, shapeIdB, manifold);
}

void DrawPolygon(const b2Vec2* vertices, int vertexCount, b2HexColor color, void* context)
{
    static_cast<World*>(context)->debug_draw_helper_.AddPolygon(vertices, vertexCount, color);
}

void DrawSolidPolygon(b2Transform transform, const b2Vec2* vertices, int vertexCount, float radius, b2HexColor color, void* context)
{
    static_cast<World*>(context)->debug_draw_helper_.AddSolidPolygon(transform, vertices, vertexCount, radius, color);
}

void DrawCircle(b2Vec2 center, float radius, b2HexColor color, void* context)
{
    static_cast<World*>(context)->debug_draw_helper_.AddCircle(center, radius, color);
}

void DrawSolidCircle(b2Transform transform, float radius, b2HexColor color, void* context)
{
    static_cast<World*>(context)->debug_draw_helper_.AddSolidCircle(transform, b2Vec2_zero, radius, color);
}

void DrawCapsule(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color, void* context)
{
    static_cast<World*>(context)->debug_draw_helper_.AddCapsule(p1, p2, radius, color);
}

void DrawSolidCapsule(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color, void* context)
{
    static_cast<World*>(context)->debug_draw_helper_.AddSolidCapsule(p1, p2, radius, color);
}

void DrawSegment(b2Vec2 p1, b2Vec2 p2, b2HexColor color, void* context)
{
    static_cast<World*>(context)->debug_draw_helper_.AddSegment(p1, p2, color);
}

void DrawTransform(b2Transform transform, void* context)
{
    static_cast<World*>(context)->debug_draw_helper_.AddTransform(transform);
}

void DrawPoint(b2Vec2 p, float size, b2HexColor color, void* context)
{
    static_cast<World*>(context)->debug_draw_helper_.AddPoint(p, size, color);
}

void DrawString(b2Vec2 p, const char* s, void* context)
{
    static_cast<World*>(context)->debug_draw_helper_.AddString(p, s);
}
