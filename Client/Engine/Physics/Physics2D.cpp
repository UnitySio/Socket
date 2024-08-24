#include "pch.h"
#include "Physics2D.h"

#include "box2d/box2d.h"
#include "box2d/math_functions.h"
#include "box2d/types.h"
#include "Level/World.h"

struct SingleOverlapContext
{
    b2BodyId owner_body_id = b2_nullBodyId;
    Actor** actor;
};

struct MultiOverlapContext
{
    b2BodyId owner_body_id = b2_nullBodyId;
    std::vector<Actor*>& actors;
};

bool SingleOverlapCallback(b2ShapeId shapeId, void* context)
{
    SingleOverlapContext* query_context = static_cast<SingleOverlapContext*>(context);
    b2BodyId body_id = b2Shape_GetBody(shapeId);
    if (B2_IS_NON_NULL(query_context->owner_body_id) && B2_ID_EQUALS(body_id, query_context->owner_body_id)) return true;

    Actor* actor = static_cast<Actor*>(b2Body_GetUserData(body_id));
    if (!actor) return true;

    *query_context->actor = actor;
    return false;
}

bool MultiOverlapCallback(b2ShapeId shapeId, void* context)
{
    MultiOverlapContext* query_context = static_cast<MultiOverlapContext*>(context);
    b2BodyId body_id = b2Shape_GetBody(shapeId);
    if (B2_IS_NON_NULL(query_context->owner_body_id) && B2_ID_EQUALS(body_id, query_context->owner_body_id)) return true;

    Actor* actor = static_cast<Actor*>(b2Body_GetUserData(body_id));
    if (!actor) return true;

    query_context->actors.push_back(actor);
    return true;
}

bool Physics2D::OverlapBox(const Math::Vector2& center, const Math::Vector2& size, const Actor* owner, Actor** output_actor, MathTypes::uint16 layer)
{
    b2Polygon box = b2MakeBox(size.x * .5f, size.y * .5f);

    b2Transform transform = b2Transform_identity;
    transform.p = {center.x, center.y};
    
    b2QueryFilter filter = b2DefaultQueryFilter();
    filter.categoryBits = layer;
    filter.maskBits = layer;

    b2BodyId owner_body_id = b2_nullBodyId;
    if (owner) owner_body_id = owner->body_id_;

    SingleOverlapContext context = {owner_body_id, output_actor};
    b2World_OverlapPolygon(World::Get()->world_id_, &box, transform, filter, SingleOverlapCallback, &context);
    if (*output_actor) return true;

    return false;
}

bool Physics2D::OverlapBoxAll(const Math::Vector2& center, const Math::Vector2& size, const Actor* owner, std::vector<Actor*>& output_actors, MathTypes::uint16 layer)
{
    b2Polygon box = b2MakeBox(size.x * .5f, size.y * .5f);

    b2Transform transform = b2Transform_identity;
    transform.p = {center.x, center.y};

    b2QueryFilter filter = b2DefaultQueryFilter();
    filter.categoryBits = layer;
    filter.maskBits = layer;

    b2BodyId owner_body_id = b2_nullBodyId;
    if (owner) owner_body_id = owner->body_id_;

    MultiOverlapContext context = {owner_body_id, output_actors};
    b2World_OverlapPolygon(World::Get()->world_id_, &box, transform, filter, MultiOverlapCallback, &context);
    if (!output_actors.empty()) return true;

    return false;
}

bool Physics2D::OverlapCircle(const Math::Vector2& center, float radius, const Actor* owner, Actor** output_actor, MathTypes::uint16 layer)
{
    b2Circle circle = {b2Vec2_zero, radius};
    
    b2Transform transform = b2Transform_identity;
    transform.p = {center.x, center.y};
    
    b2QueryFilter filter = b2DefaultQueryFilter();
    filter.categoryBits = layer;
    filter.maskBits = layer;
    
    b2BodyId owner_body_id = b2_nullBodyId;
    if (owner) owner_body_id = owner->body_id_;
    
    SingleOverlapContext context = {owner_body_id, output_actor};
    b2World_OverlapCircle(World::Get()->world_id_, &circle, transform, filter, SingleOverlapCallback, &context);
    if (*output_actor) return true;

    return false;
}

bool Physics2D::OverlapCircleAll(const Math::Vector2& center, float radius, const Actor* owner, std::vector<Actor*>& output_actors, MathTypes::uint16 layer)
{
    b2Circle circle = {b2Vec2_zero, radius};
    
    b2Transform transform = b2Transform_identity;
    transform.p = {center.x, center.y};
    
    b2QueryFilter filter = b2DefaultQueryFilter();
    filter.categoryBits = layer;
    filter.maskBits = layer;
    
    b2BodyId owner_body_id = b2_nullBodyId;
    if (owner) owner_body_id = owner->body_id_;
    
    MultiOverlapContext context = {owner_body_id, output_actors};
    b2World_OverlapCircle(World::Get()->world_id_, &circle, transform, filter, SingleOverlapCallback, &context);
    if (!output_actors.empty()) return true;

    return false;
}
