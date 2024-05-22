#include "ShapeBatch.h"

#include "Shaders.h"
#include "Shape.h"
#include "Texture.h"
#include "Vertex.h"
#include "Misc/EngineMacros.h"

ShapeBatch::ShapeBatch() :
    blend_state_(nullptr),
    rasterizer_state_(nullptr),
    depth_stencil_state_(nullptr),
    vertex_buffer_(),
    index_buffer_(),
    vertex_shader_(nullptr),
    pixel_shader_(nullptr)
{
}

bool ShapeBatch::Init()
{
    if (!vertex_buffer_.CreateBuffer(sizeof(DefaultVertex), true, false)) return false;
    if (!index_buffer_.CreateBuffer(true, false)) return false;

    vertex_shader_ = MAKE_SHARED<DefaultVertexShader>();
    pixel_shader_ = MAKE_SHARED<DefaultPixelShader>();

    D3D11_BLEND_DESC blend_desc;
    ZeroMemory(&blend_desc, sizeof(D3D11_BLEND_DESC));

    D3D11_RENDER_TARGET_BLEND_DESC render_target_blend_desc;
    ZeroMemory(&render_target_blend_desc, sizeof(D3D11_RENDER_TARGET_BLEND_DESC));

    render_target_blend_desc.BlendEnable = true;
    render_target_blend_desc.SrcBlend = D3D11_BLEND_SRC_ALPHA;
    render_target_blend_desc.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    render_target_blend_desc.BlendOp = D3D11_BLEND_OP_ADD;
    render_target_blend_desc.SrcBlendAlpha = D3D11_BLEND_ONE;
    render_target_blend_desc.DestBlendAlpha = D3D11_BLEND_ZERO;
    render_target_blend_desc.BlendOpAlpha = D3D11_BLEND_OP_ADD;
    render_target_blend_desc.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    blend_desc.RenderTarget[0] = render_target_blend_desc;

    HRESULT hr = Renderer::Get()->GetDevice()->CreateBlendState(&blend_desc, blend_state_.GetAddressOf());
    if (FAILED(hr)) return false;

    D3D11_RASTERIZER_DESC rasterizer_desc;
    ZeroMemory(&rasterizer_desc, sizeof(D3D11_RASTERIZER_DESC));

    rasterizer_desc.FillMode = D3D11_FILL_SOLID;
    rasterizer_desc.CullMode = D3D11_CULL_NONE;

    hr = Renderer::Get()->GetDevice()->CreateRasterizerState(&rasterizer_desc, rasterizer_state_.GetAddressOf());
    if (FAILED(hr)) return false;

    D3D11_DEPTH_STENCIL_DESC depth_stencil_state_desc;
    ZeroMemory(&depth_stencil_state_desc, sizeof(D3D11_DEPTH_STENCIL_DESC));

    depth_stencil_state_desc.DepthEnable = true;
    depth_stencil_state_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depth_stencil_state_desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

    hr = Renderer::Get()->GetDevice()->CreateDepthStencilState(&depth_stencil_state_desc, depth_stencil_state_.GetAddressOf());
    return SUCCEEDED(hr);
}

void ShapeBatch::DrawShapes(const SHARED_PTR<WindowsWindow>& kWindow, const std::vector<SHARED_PTR<Shape>>& kShapes)
{
    Viewport* viewport = Renderer::Get()->FindViewport(kWindow.get());
    CHECK(viewport);

    for (auto& shape : kShapes)
    {    
#pragma region 초기화 및 버퍼 업데이트
        // Buffer 메모리 잠금
        void* vertices_ptr = vertex_buffer_.Lock();
        void* indices_ptr = index_buffer_.Lock();

        CopyMemory(vertices_ptr, shape->GetVertices().data(), sizeof(DefaultVertex) * shape->GetVertices().size());
        CopyMemory(indices_ptr, shape->GetIndices().data(), sizeof(MathTypes::uint32) * shape->GetIndices().size());

        // Buffer 메모리 잠금 해제
        vertex_buffer_.Unlock();
        index_buffer_.Unlock();
#pragma endregion

#pragma region 쉐이더 및 상태 설정
        vertex_shader_->BindShader();
        pixel_shader_->BindShader();
        
        DirectX::XMMATRIX wvp_matrix = shape->GetWorldMatrix() * viewport->view_matrix * viewport->projection_matrix;
        vertex_shader_->SetWorldMatrix(wvp_matrix);

        pixel_shader_->BindParameters();

        Renderer::Get()->GetDeviceContext()->OMSetBlendState(blend_state_.Get(), nullptr, 0xffffffff);
        Renderer::Get()->GetDeviceContext()->RSSetState(rasterizer_state_.Get());
        Renderer::Get()->GetDeviceContext()->OMSetDepthStencilState(depth_stencil_state_.Get(), 0);

        Renderer::Get()->GetDeviceContext()->IASetPrimitiveTopology(shape->GetPrimitiveTopology());
#pragma endregion

#pragma region 드로우 콜
        ID3D11Buffer* buffer = vertex_buffer_.GetResource();
        vertex_shader_->BindParameters();

        constexpr MathTypes::uint32 stride = sizeof(DefaultVertex);
        constexpr MathTypes::uint32 offset = 0;
        
        Renderer::Get()->GetDeviceContext()->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
        Renderer::Get()->GetDeviceContext()->IASetIndexBuffer(index_buffer_.GetResource(), DXGI_FORMAT_R32_UINT, 0);

        if (!shape->GetIndices().empty())
        {
            Renderer::Get()->GetDeviceContext()->DrawIndexed(shape->GetIndices().size(), 0, 0);
        }
        else
        {
            Renderer::Get()->GetDeviceContext()->Draw(shape->GetVertices().size(), 0);
        }
#pragma endregion
    }
}
