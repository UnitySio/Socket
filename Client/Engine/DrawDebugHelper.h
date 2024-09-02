#pragma once
#include <vector>

#include "Singleton.h"
#include "box2d/math_functions.h"
#include "box2d/types.h"
#include "Windows/DX/Vertex.h"

class Shape;

class DrawDebugHelper : public Singleton<DrawDebugHelper>
{
public:
    DrawDebugHelper();
    virtual ~DrawDebugHelper() override = default;

private:
    friend class World;
    
    friend void DrawPolygon(const b2Vec2* vertices, int vertexCount, b2HexColor color, void* context);
    friend void DrawSolidPolygon(b2Transform transform, const b2Vec2* vertices, int vertexCount, float radius, b2HexColor color, void* context);
    friend void DrawCircle(b2Vec2 center, float radius, b2HexColor color, void* context);
    friend void DrawSolidCircle(b2Transform transform, float radius, b2HexColor color, void* context);
    friend void DrawCapsule(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color, void* context);
    friend void DrawSolidCapsule(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color, void* context);
    friend void DrawSegment(b2Vec2 p1, b2Vec2 p2, b2HexColor color, void* context);
    friend void DrawTransform(b2Transform transform, void* context);
    friend void DrawPoint(b2Vec2 p, float size, b2HexColor color, void* context);
    friend void DrawString(b2Vec2 p, const char* s, void* context);

    void AddPolygon_Internal(const b2Vec2* vertices, int vertexCount, b2HexColor color);
    void AddSolidPolygon_Internal(b2Transform transform, const b2Vec2* vertices, int vertexCount, float radius, b2HexColor color);
    void AddCircle_Internal(b2Vec2 center, float radius, b2HexColor color);
    void AddSolidCircle_Internal(b2Transform transform, b2Vec2 center, float radius, b2HexColor color);
    void AddCapsule_Internal(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color);
    void AddSolidCapsule_Internal(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color);
    void AddSegment_Internal(b2Vec2 p1, b2Vec2 p2, b2HexColor color);
    void AddTransform_Internal(b2Transform transform);
    void AddPoint_Internal(b2Vec2 p, float size, b2HexColor color);
    void AddString_Internal(b2Vec2 p, const char* string, ...);
    
    void Clear();

    std::shared_ptr<Shape> polygon_shape_;
    std::shared_ptr<Shape> circle_shape_;
    std::shared_ptr<Shape> capsule_shape_;
    std::shared_ptr<Shape> segment_shape_;
    
    std::vector<DefaultVertex> polygon_vertices_;
    std::vector<MathTypes::uint32> polygon_indices_;

    std::vector<DefaultVertex> circle_vertices_;
    std::vector<MathTypes::uint32> circle_indices_;
    
    std::vector<DefaultVertex> capsule_vertices_;
    std::vector<MathTypes::uint32> capsule_indices_;
    
    std::vector<DefaultVertex> segment_vertices_;
    
};
