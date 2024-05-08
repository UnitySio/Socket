#include "ShapeBatch.h"

#include "Shaders.h"
#include "Shape.h"
#include "Vertex.h"
#include "Misc/EngineMacros.h"

ShapeBatch::ShapeBatch() :
    point_sampler_state_wrap_(nullptr),
    blend_state_(nullptr),
    rasterizer_state_(nullptr),
    depth_stencil_state_(nullptr),
    vertex_buffer_(),
    index_buffer_(),
    vertex_shader_(nullptr),
    pixel_shader_(nullptr)
{
}

ShapeBatch::~ShapeBatch()
{
}

bool ShapeBatch::Init()
{
    D3D11_SAMPLER_DESC sampler_desc;
    ZeroMemory(&sampler_desc, sizeof(D3D11_SAMPLER_DESC));

    sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
    sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampler_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampler_desc.MinLOD = 0;
    sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

    HRESULT hr = g_d3d_device->CreateSamplerState(&sampler_desc, point_sampler_state_wrap_.GetAddressOf());
    if (FAILED(hr)) return false;

    if (!vertex_buffer_.CreateBuffer(sizeof(DefaultVertex))) return false;
    if (!index_buffer_.CreateBuffer()) return false;

    vertex_shader_ = MakeShared<DefaultVertexShader>();
    pixel_shader_ = MakeShared<DefaultPixelShader>();

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

    hr = g_d3d_device->CreateBlendState(&blend_desc, blend_state_.GetAddressOf());
    if (FAILED(hr)) return false;

    D3D11_RASTERIZER_DESC rasterizer_desc;
    ZeroMemory(&rasterizer_desc, sizeof(D3D11_RASTERIZER_DESC));

    rasterizer_desc.FillMode = D3D11_FILL_SOLID;
    rasterizer_desc.CullMode = D3D11_CULL_NONE;

    hr = g_d3d_device->CreateRasterizerState(&rasterizer_desc, rasterizer_state_.GetAddressOf());
    if (FAILED(hr)) return false;

    D3D11_DEPTH_STENCIL_DESC depth_stencil_state_desc;
    ZeroMemory(&depth_stencil_state_desc, sizeof(D3D11_DEPTH_STENCIL_DESC));

    depth_stencil_state_desc.DepthEnable = true;
    depth_stencil_state_desc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
    depth_stencil_state_desc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

    hr = g_d3d_device->CreateDepthStencilState(&depth_stencil_state_desc, depth_stencil_state_.GetAddressOf());
    return SUCCEEDED(hr);
}

void ShapeBatch::DrawShapes(const SharedPtr<WindowsWindow>& kWindow, const std::vector<SharedPtr<Shape>>& kShapes)
{
    Viewport* viewport = g_renderer->FindViewport(kWindow.get());
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
        vertex_shader_->BindParameters();

        pixel_shader_->BindParameters();

        g_d3d_device_context->OMSetBlendState(blend_state_.Get(), nullptr, 0xffffffff);
        g_d3d_device_context->RSSetState(rasterizer_state_.Get());
        g_d3d_device_context->OMSetDepthStencilState(depth_stencil_state_.Get(), 0);

        g_d3d_device_context->IASetPrimitiveTopology(shape->GetPrimitiveTopology());
#pragma endregion

#pragma region 드로우 콜
        ID3D11Buffer* buffer = vertex_buffer_.GetResource();

        constexpr MathTypes::uint32 stride = sizeof(DefaultVertex);
        constexpr MathTypes::uint32 offset = 0;

        g_d3d_device_context->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);
        g_d3d_device_context->IASetIndexBuffer(index_buffer_.GetResource(), DXGI_FORMAT_R32_UINT, 0);

        if (!shape->GetIndices().empty())
        {
            g_d3d_device_context->DrawIndexed(shape->GetIndices().size(), 0, 0);
        }
        else
        {
            g_d3d_device_context->Draw(shape->GetVertices().size(), 0);
        }
#pragma endregion
    }
}
