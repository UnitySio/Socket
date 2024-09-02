#include "pch.h"
#include "DebugDrawHelper.h"

#include "Level/World.h"
#include "Windows/DX/Shape.h"

DebugDrawHelper::DebugDrawHelper() :
    polygon_vertices_(),
    polygon_indices_(),
    circle_vertices_(),
    circle_indices_(),
    capsule_vertices_(),
    capsule_indices_(),
    segment_vertices_()
{
    polygon_shape_ = std::make_shared<Shape>();
    circle_shape_ = std::make_shared<Shape>();
    capsule_shape_ = std::make_shared<Shape>();

    segment_shape_ = std::make_shared<Shape>();
    segment_shape_->SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
}

void DebugDrawHelper::DrawDebugSegment(const Math::Vector2& kStart, const Math::Vector2& kEnd, const Math::Color& kColor)
{
    segment_vertices_.push_back({
        {kStart.x, kStart.y, 0.f},
        {kColor.r / 255.f, kColor.g / 255.f, kColor.b / 255.f, kColor.a / 255.f}
    });

    segment_vertices_.push_back({
        {kEnd.x, kEnd.y, 0.f},
        {kColor.r / 255.f, kColor.g / 255.f, kColor.b / 255.f, kColor.a / 255.f}
    });
}

void DebugDrawHelper::Clear()
{
    polygon_shape_->SetVertices(polygon_vertices_);
    polygon_shape_->SetIndices(polygon_indices_);

    circle_shape_->SetVertices(circle_vertices_);
    circle_shape_->SetIndices(circle_indices_);

    capsule_shape_->SetVertices(capsule_vertices_);
    capsule_shape_->SetIndices(capsule_indices_);

    segment_shape_->SetVertices(segment_vertices_);

    World::Get()->AddShape(polygon_shape_);
    World::Get()->AddShape(circle_shape_);
    World::Get()->AddShape(capsule_shape_);
    World::Get()->AddShape(segment_shape_);

    polygon_vertices_.clear();
    polygon_indices_.clear();

    circle_vertices_.clear();
    circle_indices_.clear();

    capsule_vertices_.clear();
    capsule_indices_.clear();

    segment_vertices_.clear();
}
