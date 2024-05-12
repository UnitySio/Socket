#pragma once
#include <d3d11.h>
#include <string>
#include <wrl/client.h>

#include "Shape.h"
#include "Math/MathTypes.h"

enum class WrapMode
{
    kReapet,
    kClamp
};

enum class FilterMode
{
    kPoint,
    kBilinear
};

class Texture : public Shape
{
public:
    Texture();
    virtual ~Texture() override = default;
    
    virtual bool Load(const std::wstring& kFileName);

    inline MathTypes::uint32 GetWidth() const { return width_; }
    inline MathTypes::uint32 GetHeight() const { return height_; }

    inline WrapMode GetWrapMode() const { return wrap_mode_; }
    inline void SetWrapMode(WrapMode mode) { wrap_mode_ = mode; }

    inline FilterMode GetFilterMode() const { return filter_mode_; }
    inline void SetFilterMode(FilterMode mode) { filter_mode_ = mode; }

private:
    friend class ShapeBatch;
    friend class Sprite;
    // 테스트
    friend class Pawn;
    
    Microsoft::WRL::ComPtr<ID3D11Resource> resource_;
    Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> resource_view_;

    MathTypes::uint32 width_;
    MathTypes::uint32 height_;

    std::vector<DefaultVertex> vertices_;
    std::vector<MathTypes::uint32> indices_;

    WrapMode wrap_mode_;
    FilterMode filter_mode_;
    
};
