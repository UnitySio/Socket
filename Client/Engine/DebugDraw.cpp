#include "DebugDraw.h"

#include "Actor/Camera.h"
#include "Graphics/Graphics.h"

DebugDraw::DebugDraw()
{
}

void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    b2Vec2 new_vertices[b2_maxPolygonVertices];
    for (int32 i = 0; i < vertexCount; ++i)
    {
        new_vertices[i] = Camera::GetInstance()->GetRenderPosition(vertices[i]);
    }
    
    Graphics::GetInstance()->DrawPolygon(new_vertices, vertexCount, color);
}

void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color)
{
    b2Vec2 new_vertices[b2_maxPolygonVertices];
    for (int32 i = 0; i < vertexCount; ++i)
    {
        new_vertices[i] = Camera::GetInstance()->GetRenderPosition(vertices[i]);
    }
    
    b2Color fill_color(color.r * .5f, color.g * .5f, color.b * .5f, .5f);
    Graphics::GetInstance()->DrawSolidPolygon(new_vertices, vertexCount, fill_color);
    
    Graphics::GetInstance()->DrawPolygon(new_vertices, vertexCount, color);
}

void DebugDraw::DrawCircle(const b2Vec2& center, float radius, const b2Color& color)
{
    b2Vec2 new_center = Camera::GetInstance()->GetRenderPosition(center);
    Graphics::GetInstance()->DrawCircle(new_center, radius, color);
}

void DebugDraw::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color)
{
    b2Vec2 new_center = Camera::GetInstance()->GetRenderPosition(center);
    
    b2Color fill_color(color.r * .5f, color.g * .5f, color.b * .5f, .5f);
    Graphics::GetInstance()->DrawSolidCircle(new_center, radius, fill_color);

    Graphics::GetInstance()->DrawCircle(new_center, radius, color);

    Graphics::GetInstance()->DrawLine(new_center, new_center + radius * axis, color);
}

void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
    b2Vec2 new_p1 = Camera::GetInstance()->GetRenderPosition(p1);
    b2Vec2 new_p2 = Camera::GetInstance()->GetRenderPosition(p2);
    
    Graphics::GetInstance()->DrawLine(new_p1, new_p2, color);
}

void DebugDraw::DrawTransform(const b2Transform& xf)
{
    Camera* camera = Camera::GetInstance();
    
    const float axis_scale = 16.f;
    b2Color red(1.f, 0.f, 0.f);
    b2Color green(0.f, 1.f, 0.f);
    b2Vec2 p1 = camera->GetRenderPosition(xf.p), p2;

    p2 = p1 + axis_scale * xf.q.GetXAxis();
    Graphics::GetInstance()->DrawLine(p1, p2, red);

    p2 = p1 + axis_scale * xf.q.GetYAxis();
    Graphics::GetInstance()->DrawLine(p1, p2, green);
}

void DebugDraw::DrawPoint(const b2Vec2& p, float size, const b2Color& color)
{
    b2Vec2 new_p = Camera::GetInstance()->GetRenderPosition(p);
    Graphics::GetInstance()->DrawSolidCircle(new_p, size / 2.f, color);
}
