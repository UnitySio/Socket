#pragma once
#include <vector>

#include "box2d/types.h"

struct DefaultVertex;

class DebugDrawHelpers
{
public:
    void AddPolygon(const b2Vec2* vertices, int vertexCount, b2HexColor color);
    void AddSolidPolygon(b2Transform transform, const b2Vec2* vertices, int vertexCount, float radius, b2HexColor color);
    void AddCapsule(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color);
    void AddSolidCapsule(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color);
    void AddSegment(b2Vec2 p1, b2Vec2 p2, b2HexColor color);
    void AddTransform(b2Transform transform);
    void Clear();

private:
    std::vector<DefaultVertex> polygon_vertices_;
    std::vector<MathTypes::uint32> polygon_indices_;
    
    std::vector<DefaultVertex> capsule_vertices_;
    std::vector<MathTypes::uint32> capsule_indices_;
    
    std::vector<DefaultVertex> segment_vertices_;
    
};
