#include "pch.h"
#include "DrawDebugHelper.h"

DrawDebugHelper::DrawDebugHelper() :
    polygon_vertices_(),
    polygon_indices_(),
    circle_vertices_(),
    circle_indices_(),
    capsule_vertices_(),
    capsule_indices_(),
    segment_vertices_()
{
}

void DrawDebugHelper::AddPolygon(const b2Vec2* vertices, int vertexCount, b2HexColor color)
{
}

void DrawDebugHelper::AddSolidPolygon(b2Transform transform, const b2Vec2* vertices, int vertexCount, float radius, b2HexColor color)
{
}

void DrawDebugHelper::AddCircle(b2Vec2 center, float radius, b2HexColor color)
{
}

void DrawDebugHelper::AddSolidCircle(b2Transform transform, b2Vec2 center, float radius, b2HexColor color)
{
}

void DrawDebugHelper::AddCapsule(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color)
{
}

void DrawDebugHelper::AddSolidCapsule(b2Vec2 p1, b2Vec2 p2, float radius, b2HexColor color)
{
}

void DrawDebugHelper::AddSegment(b2Vec2 p1, b2Vec2 p2, b2HexColor color)
{
}

void DrawDebugHelper::AddTransform(b2Transform transform)
{
}

void DrawDebugHelper::AddPoint(b2Vec2 p, float size, b2HexColor color)
{
}

void DrawDebugHelper::AddString(b2Vec2 p, const char* string, ...)
{
}

void DrawDebugHelper::Clear()
{
    polygon_vertices_.clear();
    polygon_indices_.clear();
    
    circle_vertices_.clear();
    circle_indices_.clear();
    
    capsule_vertices_.clear();
    capsule_indices_.clear();
    
    segment_vertices_.clear();
}
