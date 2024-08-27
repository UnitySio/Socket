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
    b2Vec2 p1 = vertices[vertexCount - 1];
    for (int i = 0; i < vertexCount; ++i)
    {
        b2Vec2 p2 = vertices[i];
        AddSegment(p1, p2, color);
        p1 = p2;
    }
}

void DebugDrawHelpers::AddSolidPolygon(b2Transform transform, const b2Vec2* vertices, int vertexCount, float radius, b2HexColor color)
{
    Math::Color fill_color = MakeRGBA8(color, .6f);
    Math::Color border_color = MakeRGBA8(color, 1.f);

    // Fill
    for (int i = 0; i < vertexCount; ++i)
    {
        b2Vec2 p = b2Add(transform.p, b2RotateVector(transform.q, vertices[i]));
        polygon_vertices_.push_back({
            {p.x, p.y, 0.f},
            {fill_color.r / 255.f, fill_color.g / 255.f, fill_color.b / 255.f, fill_color.a / 255.f}
        });
    }

    int last_idx = polygon_vertices_.size() - vertexCount;

    for (int i = 0; i < vertexCount - 2; ++i)
    {
        polygon_indices_.push_back(last_idx);
        polygon_indices_.push_back(last_idx + i + 1);
        polygon_indices_.push_back(last_idx + i + 2);
    }

    // Border
    b2Vec2 p1 = b2Add(transform.p, b2RotateVector(transform.q, vertices[vertexCount - 1]));
    for (int i = 0; i < vertexCount; ++i)
    {
        b2Vec2 p2 = b2Add(transform.p, b2RotateVector(transform.q, vertices[i]));
        segment_vertices_.push_back({
            {p1.x, p1.y, 0.f},
            {border_color.r / 255.f, border_color.g / 255.f, border_color.b / 255.f, border_color.a / 255.f}
        });

        segment_vertices_.push_back({
            {p2.x, p2.y, 0.f},
            {border_color.r / 255.f, border_color.g / 255.f, border_color.b / 255.f, border_color.a / 255.f}
        });
        
        p1 = p2;
    }
}

void DebugDrawHelpers::AddSolidCapsule(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color)
{
    float length;
    b2Vec2 axis = b2GetLengthAndNormalize(&length, b2Sub(p2, p1));

    const float kSegments = 16.f;
    const float kIncremnt = b2_pi / kSegments;
    float sin_incremnt = sinf(kIncremnt);
    float cos_incremnt = cosf(kIncremnt);

    b2Vec2 r1 = {-axis.y, axis.x};
    b2Vec2 v1 = b2MulAdd(p1, radius, r1);
    b2Vec2 a = v1;

    for (int i = 0; i < kSegments; ++i)
    {
        b2Vec2 r2;
        r2.x = cos_incremnt * r1.x - sin_incremnt * r1.y;
        r2.y = sin_incremnt * r1.x + cos_incremnt * r1.y;

        b2Vec2 v2 = b2MulAdd(p1, radius, r2);
        AddSegment(v1, v2, color);
        r1 = r2;
        v1 = v2;
    }

    b2Vec2 b = v1;

    r1 = {axis.y, -axis.x};
    v1 = b2MulAdd(p2, radius, r1);
    b2Vec2 c = v1;

    for (int i = 0; i < kSegments; ++i)
    {
        b2Vec2 r2;
        r2.x = cos_incremnt * r1.x - sin_incremnt * r1.y;
        r2.y = sin_incremnt * r1.x + cos_incremnt * r1.y;

        b2Vec2 v2 = b2MulAdd(p2, radius, r2);
        AddSegment(v1, v2, color);
        r1 = r2;
        v1 = v2;
    }

    b2Vec2 d = v1;

    AddSegment(a, d, color);
    AddSegment(b, c, color);
    AddSegment(p1, p2, color);
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

void DebugDrawHelpers::AddTransform(b2Transform transform)
{
    const float kAxisScale = .2f;
    b2Vec2 p1 = transform.p;

    b2Vec2 p2 = b2MulAdd(p1, kAxisScale, b2Rot_GetXAxis(transform.q));
    AddSegment(p1, p2, b2_colorRed);

    p2 = b2MulAdd(p1, kAxisScale, b2Rot_GetYAxis(transform.q));
    AddSegment(p1, p2, b2_colorGreen);
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
