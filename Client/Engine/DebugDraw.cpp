#include "DebugDraw.h"

#include "Graphics/Graphics.h"
#include "Level/Level.h"
#include "Level/World.h"

DebugDraw::DebugDraw()
{
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    b2Vec2 new_vertices[b2_maxPolygonVertices];
    for (int32 i = 0; i < vertexCount; ++i)
    {
        new_vertices[i] = World::Get()->GetLevel()->GetRenderPosition(vertices[i]);
    }
    
    Graphics::Get()->DrawPolygon(new_vertices, vertexCount, color);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    // b2Vec2 new_vertices[b2_maxPolygonVertices];
    // for (int32 i = 0; i < vertexCount; ++i)
    // {
    //     new_vertices[i] = World::Get()->GetLevel()->GetRenderPosition(vertices[i]);
    // }
    //
    // b2Color fill_color(color.r * .5f, color.g * .5f, color.b * .5f, .5f);
    // Graphics::Get()->DrawSolidPolygon(new_vertices, vertexCount, fill_color);
    //
    // Graphics::Get()->DrawPolygon(new_vertices, vertexCount, color);

    for (int32 i = 0; i < vertexCount; ++i)
    {
        b2Vec2 p1 = vertices[i];
        b2Vec2 p2 = vertices[(i + 1) % vertexCount];

        DrawSegment(p1, p2, color);
    }
}

void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
    // b2Vec2 new_center = World::Get()->GetLevel()->GetRenderPosition(center);
    // Graphics::Get()->DrawCircle(new_center, radius, color);
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
    // b2Vec2 new_center = World::Get()->GetLevel()->GetRenderPosition(center);
    //
    // b2Color fill_color(color.r * .5f, color.g * .5f, color.b * .5f, .5f);
    // Graphics::Get()->DrawSolidCircle(new_center, radius, fill_color);
    //
    // Graphics::Get()->DrawCircle(new_center, radius, color);
    //
    // Graphics::Get()->DrawLine(new_center, new_center + radius * axis, color);
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    Level* level = World::Get()->GetLevel();
    PrimitiveBatch* batch = level->GetPrimitiveBatch();

    batch->DrawLine(p1.x, p1.y, p2.x, p2.y, color.r, color.g, color.b, color.a);
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{
    constexpr float axis_scale = .5f;
    b2Color red(1.f, 0.f, 0.f);
    b2Color green(0.f, 1.f, 0.f);
    b2Vec2 p1 = xf.p, p2;

    p2 = p1 + axis_scale * xf.q.GetXAxis();
    DrawSegment(p1, p2, red);

    p2 = p1 + axis_scale * xf.q.GetYAxis();
    DrawSegment(p1, p2, green);
}

void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
    // b2Vec2 new_p = World::Get()->GetLevel()->GetRenderPosition(p);
    // Graphics::Get()->DrawSolidCircle(new_p, size / 2.f, color);

    DrawCircle(p, size / 2.f, color);
}
