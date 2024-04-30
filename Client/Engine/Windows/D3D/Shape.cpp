#include "Shape.h"

Shape::Shape() :
    vertices_(),
    indices_(),
    world_matrix_(DirectX::XMMatrixIdentity()),
    primitive_topology_(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
    UpdateMatrixx();
}

Shape::~Shape()
{
}

void Shape::UpdateMatrixx()
{
    world_matrix_ = DirectX::XMMatrixTranslation(0.f, 0.f, 0.f) *
        DirectX::XMMatrixRotationRollPitchYaw(0.f, 0.f, 0.f) *
            DirectX::XMMatrixScaling(1.f, 1.f, 1.f);
}
