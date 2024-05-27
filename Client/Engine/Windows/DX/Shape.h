#pragma once
#include <d3d11.h>
#include <vector>

#include "Vertex.h"
#include "Math/MathTypes.h"
#include "Math/Vector2.h"
#include "Misc/EngineMacros.h"

class PixelShader;
class VertexShader;
class Texture;

class Shape
{
public:
    Shape();
    virtual ~Shape() = default;

    void SetPosition(Math::Vector2 position);
    void SetScale(Math::Vector2 scale);
    void SetRotation(float rotation);

    inline void SetVertices(const std::vector<DefaultVertex>& kVertices) { vertices_ = kVertices; }
    inline void SetIndices(const std::vector<MathTypes::uint32>& kIndices) { indices_ = kIndices; }
    inline void SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY primitive_topology) { primitive_topology_ = primitive_topology; }

    inline const std::vector<DefaultVertex>& GetVertices() const { return vertices_; }
    inline const std::vector<MathTypes::uint32>& GetIndices() const { return indices_; }

    inline const DirectX::XMMATRIX& GetWorldMatrix() const { return world_matrix_; }

    inline D3D11_PRIMITIVE_TOPOLOGY GetPrimitiveTopology() const { return primitive_topology_; }

    inline void SetTexture(const SHARED_PTR<Texture>& kTexture) { texture_ = kTexture; }
    inline const SHARED_PTR<Texture>& GetTexture() const { return texture_; }

    inline void SetZOrder(int z_order) { z_order_ = z_order; }
    inline int GetZOrder() const { return z_order_; }

    inline static bool CompareZOrder(const SHARED_PTR<Shape>& lhs, const SHARED_PTR<Shape>& rhs)
    {
        return lhs->GetZOrder() < rhs->GetZOrder();
    }

protected:
    virtual void UpdateMatrixx();
    
    std::vector<DefaultVertex> vertices_;
    std::vector<MathTypes::uint32> indices_;

    DirectX::XMMATRIX world_matrix_;

    D3D11_PRIMITIVE_TOPOLOGY primitive_topology_;

    Math::Vector2 position_;
    Math::Vector2 scale_;
    Math::Vector2 pivot_;
    
    float rotation_;

    SHARED_PTR<Texture> texture_;

    int z_order_;
    
};
