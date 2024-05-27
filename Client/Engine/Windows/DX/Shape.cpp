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

void Shape::SetRotation(float rotation)
{
    rotation_ = rotation;
    UpdateMatrixx();
}

void Shape::UpdateMatrixx()
{
    world_matrix_ = DirectX::XMMatrixScaling(scale_.x, scale_.y, 1.f) *
        DirectX::XMMatrixTranslation(-pivot_.x, -pivot_.y, 0.f) *
        DirectX::XMMatrixRotationZ(rotation_) *
        DirectX::XMMatrixTranslation(pivot_.x, pivot_.y, 0.f) *
        DirectX::XMMatrixTranslation(position_.x - pivot_.x, position_.y - pivot_.y, 0.f);
}
