#include "Shape.h"

Shape::Shape() :
    vertices_(),
    indices_(),
    world_matrix_(DirectX::XMMatrixIdentity()),
    primitive_topology_(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST),
    position_(Math::Vector2::Zero()),
    scale_(Math::Vector2::One()),
    pivot_(Math::Vector2::Zero()),
    rotation_(0.f),
    texture_(nullptr),
    z_order_(0)
{
    UpdateMatrixx();
}

void Shape::SetPosition(Math::Vector2 position)
{
    position_ = position;
    UpdateMatrixx();
}

void Shape::SetScale(Math::Vector2 scale)
{
    scale_ = scale;
    UpdateMatrixx();
}

void Shape::SetPivot(Math::Vector2 pivot)
{
    pivot_ = pivot;
    UpdateMatrixx();
}

void Shape::SetRotation(float rotation)
{
    rotation_ = rotation;
    UpdateMatrixx();
}

bool Shape::CompareZOrder(const std::shared_ptr<Shape>& lhs, const std::shared_ptr<Shape>& rhs)
{
    return lhs->GetZOrder() < rhs->GetZOrder();
}

void Shape::UpdateMatrixx()
{
    if (scale_.x < 0.f) scale_.x *= -1.f;
    if (scale_.y < 0.f) scale_.y *= -1.f;
    
    world_matrix_ = DirectX::XMMatrixScaling(scale_.x, scale_.y, 1.f) * // 크기 조정
        DirectX::XMMatrixTranslation(-pivot_.x, -pivot_.y, 0.f) * // Pivot 위치로 이동
        DirectX::XMMatrixRotationZ(rotation_) * // 회전
        DirectX::XMMatrixTranslation(pivot_.x, pivot_.y, 0.f) * // 원래 위치로 이동
        DirectX::XMMatrixTranslation(position_.x - pivot_.x, position_.y - pivot_.y, 0.f); // 최종 위치로 이동
}
