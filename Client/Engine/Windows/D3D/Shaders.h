﻿#pragma once
#pragma comment(lib, "D3DCompiler.lib")

#include <string>
#include <wrl/client.h>

#include "ConstantBuffer.h"
#include "DirectXTK/VertexTypes.h"

class VertexShader
{
public:
    VertexShader();
    virtual ~VertexShader() = default;

    bool Create(const std::wstring& path, const D3D11_INPUT_ELEMENT_DESC* layout, UINT layout_count);

    void BindShader();

private:
    Microsoft::WRL::ComPtr<ID3D11VertexShader> shader_;
    Microsoft::WRL::ComPtr<ID3D10Blob> shader_buffer_;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout_;
};

class PixelShader
{
public:
    PixelShader();
    virtual ~PixelShader() = default;

    bool Create(const std::wstring& path);

    void BindShader();

private:
    Microsoft::WRL::ComPtr<ID3D11PixelShader> shader_;
    Microsoft::WRL::ComPtr<ID3D10Blob> shader_buffer_;
};

class DefaultVertexShader : public VertexShader
{
public:
    DefaultVertexShader();
    virtual ~DefaultVertexShader() override = default;

protected:
    void Update();

private:
    struct Constants
    {
        DirectX::XMMATRIX mat;
        DirectX::XMFLOAT2 uv_offset = {0.f, 0.f};
        DirectX::XMFLOAT2 uv_scale = {1.f, 1.f};
    };

    ConstantBuffer<Constants> constant_buffer_;
};

class DefaultPixelShader : public PixelShader
{
public:
    DefaultPixelShader();
    virtual ~DefaultPixelShader() override = default;

protected:
    void Update();

private:
    struct Constants
    {
        float r = 1.f;
        float g = 1.f;
        float b = 1.f;
        float a = 1.f;
    };

    ConstantBuffer<Constants> constant_buffer_;
};
