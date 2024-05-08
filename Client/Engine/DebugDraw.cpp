#include "DebugDraw.h"

#include <vector>

#include "GameEngine.h"
#include "Level/World.h"
#include "Windows/D3D/Shape.h"
#include "Windows/D3D/Vertex.h"

DebugDraw::DebugDraw()
{
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    for (int32 i = 0; i < vertexCount; i++)
    {
        b2Vec2 p1 = vertices[i];
        b2Vec2 p2 = vertices[(i + 1) % vertexCount];

        DrawSegment(p1, p2, color);
    }
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    const b2Color fill_color(color.r * .5f, color.g * .5f, color.b * .5f, color.a * .5f);

    std::vector<DefaultVertex> fill_vertices;
    for (int32 i = 0; i < vertexCount; ++i)
    {
        const b2Vec2 p = vertices[i];
        fill_vertices.push_back({ { p.x, p.y, 0.f }, { fill_color.r, fill_color.g, fill_color.b, fill_color.a } });
    }

    std::vector<uint32> fill_indices;
    for (int32 i = 1; i < vertexCount - 1; ++i)
    {
        fill_indices.push_back(0);
        fill_indices.push_back(i);
        fill_indices.push_back(i + 1);
    }
    
    SharedPtr<Shape> shape = MakeShared<Shape>();
    shape->SetVertices(fill_vertices);
    shape->SetIndices(fill_indices);
    
    g_game_world->AddShape(shape);

    DrawPolygon(vertices, vertexCount, color);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
    std::vector<DefaultVertex> vertices;
    for (int32 i = 0; i < CIRCLE_SEGMENTS; ++i)
    {
        const float theta = 2.f * b2_pi * i / CIRCLE_SEGMENTS;
        const float x = center.x + radius * cosf(theta);
        const float y = center.y + radius * sinf(theta);
        vertices.push_back({ { x, y, 0.f }, { color.r, color.g, color.b, color.a } });
    }

    vertices.push_back(vertices[0]);
    
    SharedPtr<Shape> shape = MakeShared<Shape>();
    shape->SetVertices(vertices);
    shape->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    
    g_game_world->AddShape(shape);
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
    const b2Color fill_color(color.r * .5f, color.g * .5f, color.b * .5f, color.a * .5f);

    std::vector<DefaultVertex> fill_vertices;
    fill_vertices.push_back({ { center.x, center.y, 0.f }, { fill_color.r, fill_color.g, fill_color.b, fill_color.a } });

    for (int32 i = 0; i < CIRCLE_SEGMENTS; ++i)
    {
        const float theta = 2.f * b2_pi * i / CIRCLE_SEGMENTS;
        const float x = center.x + radius * cosf(theta);
        const float y = center.y + radius * sinf(theta);
        fill_vertices.push_back({ { x, y, 0.f }, { fill_color.r, fill_color.g, fill_color.b, fill_color.a } });
    }

    fill_vertices.push_back(fill_vertices[1]);

    std::vector<uint32> fill_indices;
    for (int32 i = 0; i < CIRCLE_SEGMENTS; i++)
    {
        fill_indices.push_back(0);
        fill_indices.push_back(i + 1);
        fill_indices.push_back(i + 2);
    }
    
    SharedPtr<Shape> shape = MakeShared<Shape>();
    shape->SetVertices(fill_vertices);
    shape->SetIndices(fill_indices);

    g_game_world->AddShape(shape);
    
    DrawCircle(center, radius, color);
    DrawSegment(center, center + radius * axis, color);
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    std::vector<DefaultVertex> vertices = {
        { { p1.x, p1.y, 0.f }, { color.r, color.g, color.b, color.a } },
        { { p2.x, p2.y, 0.f }, { color.r, color.g, color.b, color.a } }
    };

    SharedPtr<Shape> shape = MakeShared<Shape>();
    shape->SetVertices(vertices);
    shape->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    
    g_game_world->AddShape(shape);
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{
    constexpr float axis_scale = .5f;
    const b2Color red(1.f, 0.f, 0.f);
    const b2Color green(0.f, 1.f, 0.f);
    const b2Vec2 p1 = xf.p;

    b2Vec2 p2 = p1 + axis_scale * xf.q.GetXAxis();
    DrawSegment(p1, p2, red);

    p2 = p1 + axis_scale * xf.q.GetYAxis();
    DrawSegment(p1, p2, green);
}

void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
    std::vector<DefaultVertex> fill_vertices;
    fill_vertices.push_back({ { p.x, p.y, 0.f }, { color.r, color.g, color.b, color.a } });

    for (int32 i = 0; i < CIRCLE_SEGMENTS; ++i)
    {
        const float theta = 2.f * b2_pi * i / CIRCLE_SEGMENTS;
        const float x = p.x + size * cosf(theta);
        const float y = p.y + size * sinf(theta);
        fill_vertices.push_back({ { x, y, 0.f }, { color.r, color.g, color.b, color.a } });
    }

    fill_vertices.push_back(fill_vertices[1]);

    std::vector<UINT> fill_indices;
    for (int32 i = 0; i < CIRCLE_SEGMENTS; i++)
    {
        fill_indices.push_back(0);
        fill_indices.push_back(i + 1);
        fill_indices.push_back(i + 2);
    }
    
    SharedPtr<Shape> shape = MakeShared<Shape>();
    shape->SetVertices(fill_vertices);
    shape->SetIndices(fill_indices);

    g_game_world->AddShape(shape);
}
