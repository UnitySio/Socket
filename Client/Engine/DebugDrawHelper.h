﻿#pragma once
#include <vector>

#include "Singleton.h"
#include "Math/Color.h"
#include "Math/Vector2.h"

struct DefaultVertex;
class Shape;

class DebugDrawHelper : public Singleton<DebugDrawHelper>
{
public:
    DebugDrawHelper();
    virtual ~DebugDrawHelper() override = default;

    void DrawSegment(const Math::Vector2& kStart, const Math::Vector2& kEnd, const Math::Color& kColor);

private:
    friend class World;

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
