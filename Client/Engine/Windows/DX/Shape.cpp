#include "Shape.h"

Shape::Shape() :
    vertices_(),
    indices_(),
    world_matrix_(DirectX::XMMatrixIdentity()),
    primitive_topology_(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST),
    position_(),
    scale_(Math::Vector2::One()),
    rotation_(0.f),
    texture_(nullptr)
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
                    DirectX::XMMatrixRotationZ(rotation_) *
                    DirectX::XMMatrixTranslation(position_.x, position_.y, 0.f);
}
