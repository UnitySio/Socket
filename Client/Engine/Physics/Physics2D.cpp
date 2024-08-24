#include "pch.h"
#include "Physics2D.h"

#include "box2d/box2d.h"
#include "box2d/math_functions.h"
#include "box2d/types.h"
#include "Level/World.h"

struct SingleQueryContext
{
    b2BodyId owner_body_id = b2_nullBodyId;
    Actor** actor;
};

struct MultiQueryContext
{
    b2BodyId owner_body_id = b2_nullBodyId;
    std::vector<Actor*>& actors;
};

bool SingleQueryCallback(b2ShapeId shapeId, void* context)
{
    SingleQueryContext* query_context = static_cast<SingleQueryContext*>(context);
    b2BodyId body_id = b2Shape_GetBody(shapeId);
    if (B2_IS_NON_NULL(query_context->owner_body_id) && B2_ID_EQUALS(body_id, query_context->owner_body_id)) return true;

    Actor* actor = static_cast<Actor*>(b2Body_GetUserData(body_id));
    if (!actor) return true;

    *query_context->actor = actor;
    return false;
}

bool MultiQueryCallback(b2ShapeId shapeId, void* context)
{
    MultiQueryContext* query_context = static_cast<MultiQueryContext*>(context);
    b2BodyId body_id = b2Shape_GetBody(shapeId);
    if (B2_IS_NON_NULL(query_context->owner_body_id) && B2_ID_EQUALS(body_id, query_context->owner_body_id)) return true;

    Actor* actor = static_cast<Actor*>(b2Body_GetUserData(body_id));
    if (!actor) return true;

    query_context->actors.push_back(actor);
    return true;
}

bool Physics2D::OverlapBox(const Math::Vector2& center, const Math::Vector2& extent, const Actor* owner, Actor** output_actor, MathTypes::uint16 layer)
{
    b2AABB aabb;
    aabb.lowerBound = {center.x - extent.x, center.y - extent.y};
    aabb.upperBound = {center.x + extent.x, center.y + extent.y};

    b2QueryFilter filter = b2DefaultQueryFilter();
    filter.categoryBits = layer;
    filter.maskBits = layer;

    b2BodyId owner_body_id = b2_nullBodyId;
    if (owner) owner_body_id = owner->body_id_;

    SingleQueryContext context = {owner_body_id, output_actor};
    b2World_OverlapAABB(World::Get()->world_id_, aabb, filter, SingleQueryCallback, &context);
    if (*output_actor) return true;

    return false;
}

bool Physics2D::OverlapBoxAll(const Math::Vector2& center, const Math::Vector2& extent, const Actor* owner, std::vector<Actor*>& output_actors, MathTypes::uint16 layer)
{
    b2AABB aabb;
    aabb.lowerBound = {center.x - extent.x, center.y - extent.y};
    aabb.upperBound = {center.x + extent.x, center.y + extent.y};

    b2QueryFilter filter = b2DefaultQueryFilter();
    filter.categoryBits = layer;
    filter.maskBits = layer;

    b2BodyId owner_body_id = b2_nullBodyId;
    if (owner) owner_body_id = owner->body_id_;

    MultiQueryContext context = {owner_body_id, output_actors};
    b2World_OverlapAABB(World::Get()->world_id_, aabb, filter, MultiQueryCallback, &context);
    if (!output_actors.empty()) return true;

    return false;
}
