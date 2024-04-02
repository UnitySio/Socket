﻿#include "SpriteBatch.h"

#include <d3d11.h>
#include "Sprite.h"

SpriteBatch::SpriteBatch(ID3D11DeviceContext* device_context)
{
    device_context_ = device_context;
    orthographic_matrix_ = DirectX::XMMatrixIdentity();

    Microsoft::WRL::ComPtr<ID3D11Device> device;
    device_context_->GetDevice(device.GetAddressOf());

    HRESULT hr = constant_buffer_.Init(device.Get(), device_context_);
    assert(SUCCEEDED(hr));

    hr = constant_pixel_buffer_.Init(device.Get(), device_context_);
    assert(SUCCEEDED(hr));
    
    D3D11_INPUT_ELEMENT_DESC layout_2d[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    constexpr UINT num_elements_2d = ARRAYSIZE(layout_2d);
    bool result = vertex_shader_.Init(device, L"..\\x64\\Debug\\VertexShader2D.cso", layout_2d, num_elements_2d);
    assert(result);

    result = pixel_shader_.Init(device, L"..\\x64\\Debug\\PixelShader2D.cso");
    assert(result);
}

void SpriteBatch::Begin(DirectX::XMMATRIX orthographic_matrix)
{
    orthographic_matrix_ = orthographic_matrix;
}

void SpriteBatch::End()
{
    orthographic_matrix_ = DirectX::XMMatrixIdentity();
}

void SpriteBatch::Draw(Sprite* sprite, const std::wstring& kName, Vector location, Vector scale, float angle)
{
    const float radian = DirectX::XMConvertToRadians(angle);
    
    device_context_->IASetInputLayout(vertex_shader_.GetInputLayout());
    device_context_->VSSetShader(vertex_shader_.GetShader(), nullptr, 0);
    device_context_->PSSetShader(pixel_shader_.GetShader(), nullptr, 0);
    
    device_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    
    const SpriteFrame& frame = sprite->sprites_[kName];
    
    const float width = (sprite->width_ * frame.scale.x) / sprite->ppu_;
    const float height = (sprite->height_ * frame.scale.y) / sprite->ppu_;

    float pivot_x = width * frame.pivot.x;
    float pivot_y = height * frame.pivot.y;

    if (scale.x < 0.f) pivot_x *= -1.f;
    if (scale.y < 0.f) pivot_y *= -1.f;

    DirectX::XMMATRIX world_matrix = DirectX::XMMatrixScaling(width * scale.x, height * scale.y, 1.f) * // 크기 조정
        DirectX::XMMatrixTranslation(-pivot_x, -pivot_y, 0.f) * // Pivot 위치로 이동
            DirectX::XMMatrixRotationZ(radian) * // 회전
                DirectX::XMMatrixTranslation(pivot_x, pivot_y, 0.f) * // 원래 위치로 이동
                    DirectX::XMMatrixTranslation(location.x - pivot_x, location.y - pivot_y, 0.f); // 최종 위치 조정

    DirectX::XMMATRIX wvp_matrix = world_matrix * orthographic_matrix_;
    
    device_context_->VSSetConstantBuffers(0, 1, constant_buffer_.GetAddressOf());
    constant_buffer_.data.mat = wvp_matrix;
    constant_buffer_.data.uv_offset = {frame.offset.x, frame.offset.y};
    constant_buffer_.data.uv_scale = {frame.scale.x, frame.scale.y};
    constant_buffer_.ApplyChanges();

    device_context_->PSSetConstantBuffers(0, 1, constant_pixel_buffer_.GetAddressOf());
    constant_pixel_buffer_.ApplyChanges();

    device_context_->PSSetShaderResources(0, 1, sprite->texture_view_.GetAddressOf());

    constexpr UINT offsets = 0;
    device_context_->IASetVertexBuffers(0, 1, sprite->vertices_.GetAddressOf(), sprite->vertices_.StridePtr(), &offsets);
    device_context_->IASetIndexBuffer(sprite->indices_.Get(), DXGI_FORMAT_R32_UINT, 0);
    device_context_->DrawIndexed(sprite->indices_.BufferSize(), 0, 0);
}