#include "Debug.h"

#include "EngineMacros.h"
#include "Level/World.h"
#include "Windows/DX/Shape.h"

void AddDebugBox(const Math::Vector2& center, const Math::Vector2& extent)
{
    std::vector<DefaultVertex> vertices = {
        { { center.x - extent.x, center.y - extent.y, 0.f }, { 1.f, 0.f, 0.f, .5f } },
        { { center.x + extent.x, center.y - extent.y, 0.f }, { 1.f, 0.f, 0.f, .5f } },
        { { center.x + extent.x, center.y + extent.y, 0.f }, { 1.f, 0.f, 0.f, .5f } },
        { { center.x - extent.x, center.y + extent.y, 0.f }, { 1.f, 0.f, 0.f, .5f } }
    };

    std::vector<MathTypes::uint32> indices = {
        0, 1, 2,
        0, 2, 3
    };
    
    SHARED_PTR<Shape> shape = MAKE_SHARED<Shape>();
    shape->SetVertices(vertices);
    shape->SetIndices(indices);
    shape->SetZOrder(32767);

    World::Get()->AddShape(shape);
}

void AddDebugCircle(const Math::Vector2& center, float radius)
{
    std::vector<DefaultVertex> fill_vertices;
    fill_vertices.push_back({ { center.x, center.y, 0.f }, { 1.f, 0.f, 0.f, .5f } });

    for (int32 i = 0; i < CIRCLE_SEGMENTS; ++i)
    {
        const float theta = 2.f * b2_pi * i / CIRCLE_SEGMENTS;
        const float x = center.x + radius * cosf(theta);
        const float y = center.y + radius * sinf(theta);
        fill_vertices.push_back({ { x, y, 0.f }, { 1.f, 0.f, 0.f, .5f } });
    }

    fill_vertices.push_back(fill_vertices[1]);

    std::vector<uint32> fill_indices;
    for (int32 i = 0; i < CIRCLE_SEGMENTS; ++i)
    {
        fill_indices.push_back(0);
        fill_indices.push_back(i + 1);
        fill_indices.push_back(i + 2);
    }
    
    SHARED_PTR<Shape> shape = MAKE_SHARED<Shape>();
    shape->SetVertices(fill_vertices);
    shape->SetIndices(fill_indices);
    shape->SetZOrder(32767);

    World::Get()->AddShape(shape);
}

void AddDebugLine(const Math::Vector2& start, const Math::Vector2& end)
{
    std::vector<DefaultVertex> vertices = {
        { { start.x, start.y, 0.f }, { 0.f, 1.f, 0.f, .5f } },
        { { end.x, end.y, 0.f }, { 0.f, 1.f, 0.f, .5f } }
    };

    SHARED_PTR<Shape> shape = MAKE_SHARED<Shape>();
    shape->SetVertices(vertices);
    shape->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    shape->SetZOrder(32767);

    World::Get()->AddShape(shape);
}
