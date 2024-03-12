#include "Sprite.h"

#include <vector>

#include "DirectXTK/WICTextureLoader.h"
#include "Time/Time.h"

Sprite::Sprite()
{
    world_matrix_ = DirectX::XMMatrixIdentity();
}

bool Sprite::Init(ID3D11Device* device, ID3D11DeviceContext* device_context,
                  const std::wstring& kPath, float ppu, ConstantBuffer<ConstantVertexBuffer2D>& constant_buffer,
                  ConstantBuffer<ConstantPixelBuffer2D>& constant_pixel_buffer)
{
    device_context_ = device_context;
    if (!device_context_) return false;

    constant_buffer_ = &constant_buffer;
    constant_pixel_buffer_ = &constant_pixel_buffer;

    HRESULT hr = DirectX::CreateWICTextureFromFile(device, kPath.c_str(), texture_.GetAddressOf(),
                                                   texture_view_.GetAddressOf());
    if (FAILED(hr)) return false;

    Microsoft::WRL::ComPtr<ID3D11Texture2D> texture;

    texture_->QueryInterface<ID3D11Texture2D>(texture.GetAddressOf());
    if (!texture) return false;

    D3D11_TEXTURE2D_DESC texture_desc;
    texture->GetDesc(&texture_desc);

    std::vector<Vertex2D> vertices =
    {
        {-.5f, -.5f, 0.f, 0.f, 1.f}, // 왼쪽 아래
        {.5f, -.5f, 0.f, 1.f, 1.f}, // 오른쪽 아래
        {-.5f, .5f, 0.f, 0.f, 0.f}, // 왼쪽 위
        {.5f, .5f, 0.f, 1.f, 0.f} // 오른쪽 위
    };

    std::vector<DWORD> indices =
    {
        0, 1, 2,
        2, 1, 3
    };

    hr = vertices_.Init(device, vertices.data(), vertices.size());
    if (FAILED(hr)) return false;

    hr = indices_.Init(device, indices.data(), indices.size());
    if (FAILED(hr)) return false;

    SetPosition(-((64.f / ppu) / 2.f),
        -((texture_desc.Height / ppu) / 2.f),
        0.f);
    
    SetRotation(0.f, 0.f, 0.f);
    SetScale(64.f / ppu, texture_desc.Height / ppu);

    return true;
}

void Sprite::Draw(DirectX::XMMATRIX orthographic_matrix)
{
    DirectX::XMMATRIX wvp_matrix = world_matrix_ * orthographic_matrix;
    device_context_->VSSetConstantBuffers(0, 1, constant_buffer_->GetAddressOf());
    constant_buffer_->data.mat = wvp_matrix;
    constant_buffer_->ApplyChanges();

    device_context_->PSSetConstantBuffers(0, 1, constant_pixel_buffer_->GetAddressOf());
    constant_pixel_buffer_->ApplyChanges();

    static float x_offset = 0.f;
    x_offset += .5f * Time::DeltaTime();

    static float y_offset = 0.f;
    y_offset += .5f * Time::DeltaTime();

    constant_buffer_->data.uv_offset = {x_offset, y_offset};
    
    float width_scale = 64.f / 384.f;
    float height_scale = 1.f;

    constant_buffer_->data.uv_scale = {width_scale, height_scale};

    device_context_->PSSetShaderResources(0, 1, texture_view_.GetAddressOf());

    constexpr UINT offsets = 0;
    device_context_->IASetVertexBuffers(0, 1, vertices_.GetAddressOf(), vertices_.StridePtr(), &offsets);
    device_context_->IASetIndexBuffer(indices_.Get(), DXGI_FORMAT_R32_UINT, 0);
    device_context_->DrawIndexed(indices_.BufferSize(), 0, 0);
}

void Sprite::SetPosition(float x, float y, float z)
{
    position_ = {x, y, z};
    position_vector_ = DirectX::XMLoadFloat3(&position_);
    UpdateMatrix();
}

void Sprite::SetPosition(const DirectX::XMVECTOR& position)
{
    DirectX::XMStoreFloat3(&position_, position);
    position_vector_ = position;
    UpdateMatrix();
}

void Sprite::AdjustPosition(float x, float y, float z)
{
    position_.x += x;
    position_.y += y;
    position_.z += z;
    position_vector_ = DirectX::XMLoadFloat3(&position_);
    UpdateMatrix();
}

void Sprite::AdjustPosition(const DirectX::XMVECTOR& position)
{
    position_vector_ = DirectX::XMVectorAdd(position_vector_, position);
    DirectX::XMStoreFloat3(&position_, position_vector_);
    UpdateMatrix();
}

void Sprite::SetRotation(float x, float y, float z)
{
    rotation_ = {x, y, z};
    rotation_vector_ = DirectX::XMLoadFloat3(&rotation_);
    UpdateMatrix();
}

void Sprite::SetRotation(const DirectX::XMVECTOR& rotation)
{
    rotation_vector_ = rotation;
    DirectX::XMStoreFloat3(&rotation_, rotation);
    UpdateMatrix();
}

void Sprite::AdjustRotation(float x, float y, float z)
{
    rotation_.x += x;
    rotation_.y += y;
    rotation_.z += z;
    rotation_vector_ = DirectX::XMLoadFloat3(&rotation_);
    UpdateMatrix();
}

void Sprite::AdjustRotation(const DirectX::XMVECTOR& rotation)
{
    rotation_vector_ = DirectX::XMVectorAdd(rotation_vector_, rotation);
    DirectX::XMStoreFloat3(&rotation_, rotation_vector_);
    UpdateMatrix();
}

void Sprite::SetScale(float x, float y, float z)
{
    scale_ = {x, y, z};
    UpdateMatrix();
}

void Sprite::UpdateMatrix()
{
    world_matrix_ = DirectX::XMMatrixScaling(scale_.x, scale_.y, 1.f) *
        DirectX::XMMatrixRotationRollPitchYaw(rotation_.x, rotation_.y, rotation_.z) *
        DirectX::XMMatrixTranslation(position_.x + scale_.x / 2.f, position_.y + scale_.y / 2.f, position_.z);
}
