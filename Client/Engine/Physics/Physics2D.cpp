#include "pch.h"
#include "Physics2D.h"

#include "box2d/box2d.h"
#include "box2d/math_functions.h"
#include "box2d/types.h"
#include "Level/World.h"

struct QueryContext
{
    b2BodyId owner_body_id = b2_nullBodyId;
    Actor* actor = nullptr;
};

bool QueryCallback(b2ShapeId shapeId, void* context)
{
    QueryContext* query_context = static_cast<QueryContext*>(context);
    b2BodyId body_id = b2Shape_GetBody(shapeId);
    if (B2_IS_NON_NULL(query_context->owner_body_id) && B2_ID_EQUALS(body_id, query_context->owner_body_id)) return true;

    Actor* actor = static_cast<Actor*>(b2Body_GetUserData(body_id));
    if (!actor) return true;

    query_context->actor = actor;
    return false;
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

    QueryContext context = {owner_body_id, nullptr};
    b2World_OverlapAABB(World::Get()->world_id_, aabb, filter, QueryCallback, &context);
    if (context.actor)
    {
        *output_actor = context.actor;
        return true;
    }

    return false;
}
