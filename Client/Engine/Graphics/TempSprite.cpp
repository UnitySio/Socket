#include "TempSprite.h"

#include "Texture.h"
#include "DirectXTK/WICTextureLoader.h"
#include "Time/Time.h"

TempSprite::TempSprite()
{
    world_matrix_ = DirectX::XMMatrixIdentity();
}

bool TempSprite::Init(ID3D11DeviceContext* device_context, Texture* texture, float ppu,
                  ConstantBuffer<ConstantVertexBuffer2D>& constant_buffer,
                  ConstantBuffer<ConstantPixelBuffer2D>& constant_pixel_buffer)
{
    device_context_ = device_context;
    if (!device_context_) return false;

    constant_buffer_ = &constant_buffer;
    constant_pixel_buffer_ = &constant_pixel_buffer;

    int row = texture->height_ / 64.f;
    int col = texture->width_ / 64.f;

    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            TempSpriteFrame frame;
            frame.offset_x = j;
            frame.offset_y = i;
            frame.scale_x = 64.f / texture->width_;
            frame.scale_y = 64.f / texture->height_;
            frames_.push_back(frame);
        }
    }

    SetPosition(-((64.f / ppu) / 2.f),
                -((texture->height_ / ppu) / 2.f),
                0.f);

    SetRotation(0.f, 0.f, 0.f);
    SetScale(64.f / ppu, texture->height_ / ppu);
    
    texture_ = texture;

    return true;
}

void TempSprite::Draw(DirectX::XMMATRIX orthographic_matrix)
{
    DirectX::XMMATRIX wvp_matrix = world_matrix_ * orthographic_matrix;
    device_context_->VSSetConstantBuffers(0, 1, constant_buffer_->GetAddressOf());
    constant_buffer_->data.mat = wvp_matrix;
    constant_buffer_->ApplyChanges();

    device_context_->PSSetConstantBuffers(0, 1, constant_pixel_buffer_->GetAddressOf());
    constant_pixel_buffer_->ApplyChanges();

    static float timer = 0.f;
    timer += Time::DeltaTime();

    static int frame_index = 0;
    if (timer >= 1.f / 10.f)
    {
        frame_index = (frame_index + 1) % frames_.size();
        timer = 0.f;
    }

    TempSpriteFrame frame = frames_[frame_index];
    constant_buffer_->data.uv_offset = {frame.offset_x, frame.offset_y};
    constant_buffer_->data.uv_scale = {frame.scale_x, frame.scale_y};

    device_context_->PSSetShaderResources(0, 1, texture_->texture_view_.GetAddressOf());

    constexpr UINT offsets = 0;
    device_context_->IASetVertexBuffers(0, 1, texture_->vertices_.GetAddressOf(), texture_->vertices_.StridePtr(), &offsets);
    device_context_->IASetIndexBuffer(texture_->indices_.Get(), DXGI_FORMAT_R32_UINT, 0);
    device_context_->DrawIndexed(texture_->indices_.BufferSize(), 0, 0);
}

void TempSprite::SetPosition(float x, float y, float z)
{
    position_ = {x, y, z};
    position_vector_ = DirectX::XMLoadFloat3(&position_);
    UpdateMatrix();
}

void TempSprite::SetPosition(const DirectX::XMVECTOR& position)
{
    DirectX::XMStoreFloat3(&position_, position);
    position_vector_ = position;
    UpdateMatrix();
}

void TempSprite::AdjustPosition(float x, float y, float z)
{
    position_.x += x;
    position_.y += y;
    position_.z += z;
    position_vector_ = DirectX::XMLoadFloat3(&position_);
    UpdateMatrix();
}

void TempSprite::AdjustPosition(const DirectX::XMVECTOR& position)
{
    position_vector_ = DirectX::XMVectorAdd(position_vector_, position);
    DirectX::XMStoreFloat3(&position_, position_vector_);
    UpdateMatrix();
}

void TempSprite::SetRotation(float x, float y, float z)
{
    rotation_ = {x, y, z};
    rotation_vector_ = DirectX::XMLoadFloat3(&rotation_);
    UpdateMatrix();
}

void TempSprite::SetRotation(const DirectX::XMVECTOR& rotation)
{
    rotation_vector_ = rotation;
    DirectX::XMStoreFloat3(&rotation_, rotation);
    UpdateMatrix();
}

void TempSprite::AdjustRotation(float x, float y, float z)
{
    rotation_.x += x;
    rotation_.y += y;
    rotation_.z += z;
    rotation_vector_ = DirectX::XMLoadFloat3(&rotation_);
    UpdateMatrix();
}

void TempSprite::AdjustRotation(const DirectX::XMVECTOR& rotation)
{
    rotation_vector_ = DirectX::XMVectorAdd(rotation_vector_, rotation);
    DirectX::XMStoreFloat3(&rotation_, rotation_vector_);
    UpdateMatrix();
}

void TempSprite::SetScale(float x, float y, float z)
{
    scale_ = {x, y, z};
    UpdateMatrix();
}

void TempSprite::UpdateMatrix()
{
    world_matrix_ = DirectX::XMMatrixScaling(scale_.x, scale_.y, 1.f) *
        DirectX::XMMatrixRotationRollPitchYaw(rotation_.x, rotation_.y, rotation_.z) *
        DirectX::XMMatrixTranslation(position_.x + scale_.x / 2.f, position_.y + scale_.y / 2.f, position_.z);
}
