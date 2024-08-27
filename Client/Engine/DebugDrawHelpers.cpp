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

void DebugDrawHelpers::AddSolidPolygon(b2Transform transform, const b2Vec2* vertices, int vertexCount, float radius, b2HexColor color)
{
    Math::Color rgba8 = MakeRGBA8(color, .5f);

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
}

void DebugDrawHelpers::CreateShape()
{
    std::shared_ptr<Shape> shape = std::make_shared<Shape>();
    shape->SetVertices(polygon_vertices_);
    shape->SetIndices(polygon_indices_);

    World::Get()->AddShape(shape);
}

void DebugDrawHelpers::Flush()
{
    polygon_vertices_.clear();
    polygon_indices_.clear();
}
