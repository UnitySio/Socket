#include "pch.h"
#include "DrawDebugHelper.h"

#include "Level/World.h"
#include "Windows/DX/Shape.h"

DrawDebugHelper::DrawDebugHelper() :
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

void DrawDebugHelper::AddPolygon_Internal(const b2Vec2* vertices, int vertexCount, b2HexColor color)
{
}

void DrawDebugHelper::AddSolidPolygon_Internal(b2Transform transform, const b2Vec2* vertices, int vertexCount, float radius, b2HexColor color)
{
}

void DrawDebugHelper::AddCircle_Internal(b2Vec2 center, float radius, b2HexColor color)
{
}

void DrawDebugHelper::AddSolidCircle_Internal(b2Transform transform, b2Vec2 center, float radius, b2HexColor color)
{
}

void DrawDebugHelper::AddCapsule_Internal(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color)
{
}

void DrawDebugHelper::AddSolidCapsule_Internal(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color)
{
}

void DrawDebugHelper::AddSegment_Internal(b2Vec2 p1, b2Vec2 p2, b2HexColor color)
{
}

void DrawDebugHelper::AddTransform_Internal(b2Transform transform)
{
}

void DrawDebugHelper::AddPoint_Internal(b2Vec2 p, float size, b2HexColor color)
{
}

void DrawDebugHelper::AddString_Internal(b2Vec2 p, const char* string, ...)
{
}

void DrawDebugHelper::Clear()
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
