#include "DebugDraw.h"

#include "Graphics/Graphics.h"
#include "Level/Level.h"
#include "Level/World.h"

#define SEGMENTS 16

DebugDraw::DebugDraw()
{
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    for (int32 i = 0; i < vertexCount; ++i)
    {
        b2Vec2 p1 = vertices[i];
        b2Vec2 p2 = vertices[(i + 1) % vertexCount];

        DrawSegment(p1, p2, color);
    }
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    const b2Color fill_color(color.r * .5f, color.g * .5f, color.b * .5f, .5f);

    std::vector<VertexPrimitive> vertex_primitives;
    for (int32 i = 0; i < vertexCount; ++i)
    {
        b2Vec2 p = vertices[i];
        vertex_primitives.push_back(VertexPrimitive(p.x, p.y, 0.f, fill_color.r, fill_color.g, fill_color.b, fill_color.a));
    }

    std::vector<UINT> indices;
    for (int32 i = 1; i < vertexCount - 1; i++)
    {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(i + 1);
    }
    
    Level* level = World::Get()->GetLevel();
    PrimitiveBatch* batch = level->GetPrimitiveBatch();
    batch->DrawSolidPolygon(vertex_primitives, indices);

    DrawPolygon(vertices, vertexCount, color);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
    std::vector<VertexPrimitive> vertices;
    for (int32 i = 0; i < SEGMENTS; ++i)
    {
        //정점이 모두 연결되어야 해
        float theta = 2.f * b2_pi * i / SEGMENTS;
        float x = center.x + radius * cos(theta);
        float y = center.y + radius * sin(theta);
        vertices.push_back(VertexPrimitive(x, y, 0.f, color.r, color.g, color.b, color.a));
    }

    vertices.push_back(vertices[0]);
    
    Level* level = World::Get()->GetLevel();
    PrimitiveBatch* batch = level->GetPrimitiveBatch();
    batch->DrawPolygon(vertices);
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
    b2Color fill_color(color.r * .5f, color.g * .5f, color.b * .5f, .5f);

    std::vector<VertexPrimitive> vertices;
    vertices.push_back(VertexPrimitive(center.x, center.y, 0.f, fill_color.r, fill_color.g, fill_color.b, fill_color.a));
    
    for (int32 i = 0; i < SEGMENTS; ++i)
    {
        float theta = 2.f * b2_pi * i / SEGMENTS;
        float x = center.x + radius * cos(theta);
        float y = center.y + radius * sin(theta);
        vertices.push_back(VertexPrimitive(x, y, 0.f, fill_color.r, fill_color.g, fill_color.b, fill_color.a));
    }

    vertices.push_back(vertices[1]);

    std::vector<UINT> indices;
    for (int32 i = 0; i < SEGMENTS; i++)
    {
        indices.push_back(0);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
    }
    
    Level* level = World::Get()->GetLevel();
    PrimitiveBatch* batch = level->GetPrimitiveBatch();
    batch->DrawSolidPolygon(vertices, indices);

    DrawCircle(center, radius, color);
    DrawSegment(center, center + radius * axis, color);
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    std::vector<VertexPrimitive> vertices = {
        VertexPrimitive(p1.x, p1.y, 0.f, color.r, color.g, color.b, color.a),
        VertexPrimitive(p2.x, p2.y, 0.f, color.r, color.g, color.b, color.a)
    };

    Level* level = World::Get()->GetLevel();
    PrimitiveBatch* batch = level->GetPrimitiveBatch();
    batch->DrawLine(vertices);
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
    size *= .025f;
    
    std::vector<VertexPrimitive> vertices;
    vertices.push_back(VertexPrimitive(p.x, p.y, 0.f, color.r, color.g, color.b, color.a));
    
    for (int32 i = 0; i < SEGMENTS; ++i)
    {
        float theta = 2.f * b2_pi * i / SEGMENTS;
        float x = p.x + size * cos(theta);
        float y = p.y + size * sin(theta);
        vertices.push_back(VertexPrimitive(x, y, 0.f, color.r, color.g, color.b, color.a));
    }

    vertices.push_back(vertices[1]);

    std::vector<UINT> indices;
    for (int32 i = 0; i < SEGMENTS; i++)
    {
        indices.push_back(0);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
    }
    
    Level* level = World::Get()->GetLevel();
    PrimitiveBatch* batch = level->GetPrimitiveBatch();
    batch->DrawSolidPolygon(vertices, indices);
}
