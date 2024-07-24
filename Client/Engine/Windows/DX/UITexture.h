#pragma once
#include <wrl/client.h>

#include <string>
#include <d2d1.h>

#include "Math/MathTypes.h"
#include "Resource/Resource.h"

class UITexture : public Resource
{
public:
    UITexture();
    virtual ~UITexture() override = default;

    virtual bool Load(const std::wstring& kPath) override;

    inline Microsoft::WRL::ComPtr<ID2D1Bitmap> GetTexture() const { return bitmap_; }
    
    inline MathTypes::uint32 GetWidth() const { return width_; }
    inline MathTypes::uint32 GetHeight() const { return height_; }

private:
    Microsoft::WRL::ComPtr<ID2D1Bitmap> bitmap_;
    
    MathTypes::uint32 width_;
    MathTypes::uint32 height_;
    
};
