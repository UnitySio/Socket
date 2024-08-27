#include "pch.h"
#include "DebugDrawHelpers.h"

#include "Level/World.h"
#include "Windows/DX/Shape.h"

static inline Math::Color MakeRGBA8(b2HexColor color, float alpha)
{
    return {
        static_cast<MathTypes::uint8>((color >> 16) & 0xFF),
        static_cast<MathTypes::uint8>((color >> 8) & 0xFF),
        static_cast<MathTypes::uint8>(color & 0xFF),
        static_cast<MathTypes::uint8>(0xFF * alpha)
    };
}

void DebugDrawHelpers::AddPolygon(const b2Vec2* vertices, int vertexCount, b2HexColor color)
{
    for (int i = 0; i < vertexCount; ++i)
    {
        b2Vec2 p1 = vertices[i];
        b2Vec2 p2 = vertices[(i + 1) % vertexCount];

        AddSegment(p1, p2, color);
    }
}

void DebugDrawHelpers::AddSolidPolygon(b2Transform transform, const b2Vec2* vertices, int vertexCount, float radius, b2HexColor color)
{
    Math::Color rgba8 = MakeRGBA8(color, .6f);

    for (int i = 0; i < vertexCount; ++i)
    {
        b2Vec2 p = b2Add(transform.p, b2RotateVector(transform.q, vertices[i]));
        polygon_vertices_.push_back({
            {p.x, p.y, 0.f},
            {rgba8.r / 255.f, rgba8.g / 255.f, rgba8.b / 255.f, rgba8.a / 255.f}
        });
    }

    int last_idx = polygon_vertices_.size() - vertexCount;

    for (int i = 0; i < vertexCount - 2; ++i)
    {
        polygon_indices_.push_back(last_idx);
        polygon_indices_.push_back(last_idx + i + 1);
        polygon_indices_.push_back(last_idx + i + 2);
    }

    AddPolygon(vertices, vertexCount, color);
}

void DebugDrawHelpers::AddSegment(b2Vec2 p1, b2Vec2 p2, b2HexColor color)
{
    Math::Color rgba8 = MakeRGBA8(color, 1.f);

    segment_vertices_.push_back({
        {p1.x, p1.y, 0.f},
        {rgba8.r / 255.f, rgba8.g / 255.f, rgba8.b / 255.f, rgba8.a / 255.f}
    });

    segment_vertices_.push_back({
        {p2.x, p2.y, 0.f},
        {rgba8.r / 255.f, rgba8.g / 255.f, rgba8.b / 255.f, rgba8.a / 255.f}
    });
}

void DebugDrawHelpers::Clear()
{
    std::shared_ptr<Shape> polygon = std::make_shared<Shape>();
    polygon->SetVertices(polygon_vertices_);
    polygon->SetIndices(polygon_indices_);

    std::shared_ptr<Shape> segment = std::make_shared<Shape>();
    segment->SetVertices(segment_vertices_);
    segment->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    
    World::Get()->AddShape(polygon);
    World::Get()->AddShape(segment);
    
    polygon_vertices_.clear();
    polygon_indices_.clear();

    segment_vertices_.clear();
}
