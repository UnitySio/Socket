#pragma once
#include <vector>

#include "box2d/types.h"

struct DefaultVertex;

class DebugDrawHelpers
{
public:
    void AddSolidPolygon(b2Transform transform, const b2Vec2* vertices, int vertexCount, float radius, b2HexColor color);
    void CreateShape();
    void Flush();

private:
    std::vector<DefaultVertex> polygon_vertices_;
    std::vector<MathTypes::uint32> polygon_indices_;
    
};
