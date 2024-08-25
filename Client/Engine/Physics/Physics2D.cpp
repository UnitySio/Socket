﻿#include "pch.h"
#include "Physics2D.h"

#include "box2d/box2d.h"
#include "box2d/math_functions.h"
#include "box2d/types.h"
#include "Level/World.h"
#include "Logger/Logger.h"

struct SingleOverlapContext
{
    Actor** actor;
};

struct MultiOverlapContext
{
    std::vector<Actor*>& actors;
};

struct SingleRayCastContext
{
    Math::Vector2 start;
    Math::Vector2 end;
    
    HitResult& hit_result;
};

struct MultiRayCastContext
{
    Math::Vector2 start;
    Math::Vector2 end;
    
    std::vector<HitResult>& hit_results;
};

bool SingleOverlapCallback(b2ShapeId shapeId, void* context)
{
    SingleOverlapContext* overlap_context = static_cast<SingleOverlapContext*>(context);
    
    b2BodyId body_id = b2Shape_GetBody(shapeId);
    Actor* actor = static_cast<Actor*>(b2Body_GetUserData(body_id));
    if (!actor) return true;

    *overlap_context->actor = actor;
    return false;
}

bool MultiOverlapCallback(b2ShapeId shapeId, void* context)
{
    MultiOverlapContext* overlap_context = static_cast<MultiOverlapContext*>(context);
    
    b2BodyId body_id = b2Shape_GetBody(shapeId);
    Actor* actor = static_cast<Actor*>(b2Body_GetUserData(body_id));
    if (!actor) return true;

    overlap_context->actors.push_back(actor);
    return true;
}

float SingleRayCastCallback(b2ShapeId shapeId, b2Vec2 point, b2Vec2 normal, float fraction, void* context)
{
    SingleRayCastContext* ray_cast_context = static_cast<SingleRayCastContext*>(context);
    b2BodyId body_id = b2Shape_GetBody(shapeId);

    Actor* actor = static_cast<Actor*>(b2Body_GetUserData(body_id));
    if (!actor) return -1.f;

    HitResult& hit_result = ray_cast_context->hit_result;

    hit_result.actor = actor;
    hit_result.start = ray_cast_context->start;
    hit_result.end = ray_cast_context->end;
    hit_result.point = {point.x, point.y};
    hit_result.normal = {normal.x, normal.y};
    
    float ray_length = Math::Vector2(ray_cast_context->end - ray_cast_context->start).Magnitude();
    hit_result.distance = ray_length * fraction;
    
    return 0.f;
}

float MultiRayCastCallback(b2ShapeId shapeId, b2Vec2 point, b2Vec2 normal, float fraction, void* context)
{
    MultiRayCastContext* ray_cast_context = static_cast<MultiRayCastContext*>(context);
    b2BodyId body_id = b2Shape_GetBody(shapeId);

    Actor* actor = static_cast<Actor*>(b2Body_GetUserData(body_id));
    if (!actor) return -1.f;

    HitResult hit_result;
    hit_result.actor = actor;
    hit_result.start = ray_cast_context->start;
    hit_result.end = ray_cast_context->end;
    hit_result.point = {point.x, point.y};
    hit_result.normal = {normal.x, normal.y};
    
    float ray_length = Math::Vector2(ray_cast_context->end - ray_cast_context->start).Magnitude();
    hit_result.distance = ray_length * fraction;
    
    ray_cast_context->hit_results.push_back(hit_result);
    
    return 1.f;
}

bool Physics2D::OverlapBox(const Math::Vector2& kCenter, const Math::Vector2& kSize, Actor** output_actor, MathTypes::uint16 layer)
{
    b2Polygon box = b2MakeBox(kSize.x * .5f, kSize.y * .5f);

    b2Transform transform = b2Transform_identity;
    transform.p = {kCenter.x, kCenter.y};
    
    b2QueryFilter filter = b2DefaultQueryFilter();
    filter.categoryBits = layer;
    filter.maskBits = layer;

    SingleOverlapContext context = {output_actor};
    b2World_OverlapPolygon(World::Get()->world_id_, &box, transform, filter, SingleOverlapCallback, &context);
    if (*output_actor) return true;

    return false;
}

bool Physics2D::OverlapBoxAll(const Math::Vector2& kCenter, const Math::Vector2& kSize, std::vector<Actor*>& output_actors, MathTypes::uint16 layer)
{
    b2Polygon box = b2MakeBox(kSize.x * .5f, kSize.y * .5f);

    b2Transform transform = b2Transform_identity;
    transform.p = {kCenter.x, kCenter.y};

    b2QueryFilter filter = b2DefaultQueryFilter();
    filter.categoryBits = layer;
    filter.maskBits = layer;

    MultiOverlapContext context = {output_actors};
    b2World_OverlapPolygon(World::Get()->world_id_, &box, transform, filter, MultiOverlapCallback, &context);
    if (!output_actors.empty()) return true;

    return false;
}

bool Physics2D::OverlapCircle(const Math::Vector2& kCenter, float radius, Actor** output_actor, MathTypes::uint16 layer)
{
    b2Circle circle = {b2Vec2_zero, radius};
    
    b2Transform transform = b2Transform_identity;
    transform.p = {kCenter.x, kCenter.y};
    
    b2QueryFilter filter = b2DefaultQueryFilter();
    filter.categoryBits = layer;
    filter.maskBits = layer;
    
    SingleOverlapContext context = {output_actor};
    b2World_OverlapCircle(World::Get()->world_id_, &circle, transform, filter, SingleOverlapCallback, &context);
    if (*output_actor) return true;

    return false;
}

bool Physics2D::OverlapCircleAll(const Math::Vector2& kCenter, float radius, std::vector<Actor*>& output_actors, MathTypes::uint16 layer)
{
    b2Circle circle = {b2Vec2_zero, radius};
    
    b2Transform transform = b2Transform_identity;
    transform.p = {kCenter.x, kCenter.y};
    
    b2QueryFilter filter = b2DefaultQueryFilter();
    filter.categoryBits = layer;
    filter.maskBits = layer;
    
    MultiOverlapContext context = {output_actors};
    b2World_OverlapCircle(World::Get()->world_id_, &circle, transform, filter, SingleOverlapCallback, &context);
    if (!output_actors.empty()) return true;

    return false;
}

bool Physics2D::RayCast(HitResult& hit_result, const Math::Vector2& kOrigin, const Math::Vector2& kDirection, float max_distance, MathTypes::uint16 layer)
{
    b2QueryFilter filter = b2DefaultQueryFilter();
    filter.categoryBits = layer;
    filter.maskBits = layer;

    Math::Vector2 translation = {kDirection.x * max_distance, kDirection.y * max_distance};
    
    SingleRayCastContext context = {kOrigin, {kOrigin.x + translation.x, kOrigin.y + translation.y}, hit_result};
    b2World_CastRay(World::Get()->world_id_, {kOrigin.x, kOrigin.y}, {translation.x, translation.y}, filter, SingleRayCastCallback, &context);
    if (hit_result.actor) return true;
    
    return false;
}

bool Physics2D::RayCastAll(std::vector<HitResult>& hit_results, const Math::Vector2& kOrigin, const Math::Vector2& kDirection, float max_distance, MathTypes::uint16 layer)
{
    b2QueryFilter filter = b2DefaultQueryFilter();
    filter.categoryBits = layer;
    filter.maskBits = layer;

    Math::Vector2 translation = {kDirection.x * max_distance, kDirection.y * max_distance};

    MultiRayCastContext context = {kOrigin, {kOrigin.x + translation.x, kOrigin.y + translation.y}, hit_results};
    b2World_CastRay(World::Get()->world_id_, {kOrigin.x, kOrigin.y}, {translation.x, translation.y}, filter, MultiRayCastCallback, &context);
    if (!hit_results.empty()) return true;

    return false;
}

bool Physics2D::BoxCast(HitResult& hit_result, const Math::Vector2& kSize, float angle, const Math::Vector2& kOrigin, const Math::Vector2& kDirection, float max_distance, MathTypes::uint16 layer)
{
    b2Polygon box = b2MakeBox(kSize.x * .5f, kSize.y * .5f);
    b2Transform transform = {{kOrigin.x, kOrigin.y}, b2MakeRot(angle * MATH_PI / 180.f)};
    
    b2QueryFilter filter = b2DefaultQueryFilter();
    filter.categoryBits = layer;
    filter.maskBits = layer;
    
    Math::Vector2 translation = {kDirection.x * max_distance, kDirection.y * max_distance};

    SingleRayCastContext context = {kOrigin, {kOrigin.x + translation.x, kOrigin.y + translation.y}, hit_result};
    b2World_CastPolygon(World::Get()->world_id_, &box, transform, {translation.x, translation.y}, filter, SingleRayCastCallback, &context);
    if (hit_result.actor) return true;

    return false;
}

bool Physics2D::BoxCastAll(std::vector<HitResult>& hit_results, const Math::Vector2& kSize, float angle, const Math::Vector2& kOrigin, const Math::Vector2& kDirection, float max_distance, MathTypes::uint16 layer)
{
    b2Polygon box = b2MakeBox(kSize.x * .5f, kSize.y * .5f);
    b2Transform transform = {{kOrigin.x, kOrigin.y}, b2MakeRot(angle * MATH_PI / 180.f)};
    
    b2QueryFilter filter = b2DefaultQueryFilter();
    filter.categoryBits = layer;
    filter.maskBits = layer;
    
    Math::Vector2 translation = {kDirection.x * max_distance, kDirection.y * max_distance};

    MultiRayCastContext context = {kOrigin, {kOrigin.x + translation.x, kOrigin.y + translation.y}, hit_results};
    b2World_CastPolygon(World::Get()->world_id_, &box, transform, {translation.x, translation.y}, filter, MultiRayCastCallback, &context);
    if (!hit_results.empty()) return true;

    return false;
}
