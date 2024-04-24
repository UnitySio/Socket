#pragma once
#pragma comment(lib, "D3DCompiler.lib")

#include <string>
#include <wrl/client.h>

#include "DirectXTK/VertexTypes.h"

class VertexShader
{
public:
    VertexShader();
    ~VertexShader() = default;

    bool Create(const std::wstring& path, const D3D11_INPUT_ELEMENT_DESC* layout, UINT layout_count);

    void BindShader();

    inline ID3D11VertexShader* GetShader() const { return shader_.Get(); }
    inline ID3D10Blob* GetShaderBuffer() const { return shader_buffer_.Get(); }
    inline ID3D11InputLayout* GetInputLayout() const { return input_layout_.Get(); }

private:
    Microsoft::WRL::ComPtr<ID3D11VertexShader> shader_;
    Microsoft::WRL::ComPtr<ID3D10Blob> shader_buffer_;
    Microsoft::WRL::ComPtr<ID3D11InputLayout> input_layout_;
    
};

class PixelShader
{
public:
    PixelShader();
    ~PixelShader() = default;

    bool Create(const std::wstring& path);

    void BindShader();

    inline ID3D11PixelShader* GetShader() const { return shader_.Get(); }
    inline ID3D10Blob* GetShaderBuffer() const { return shader_buffer_.Get(); }

private:
    Microsoft::WRL::ComPtr<ID3D11PixelShader> shader_;
    Microsoft::WRL::ComPtr<ID3D10Blob> shader_buffer_;
    
};
