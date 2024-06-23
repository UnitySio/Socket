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
    shape->SetZOrder(10);

    World::Get()->AddShape(shape);
}
