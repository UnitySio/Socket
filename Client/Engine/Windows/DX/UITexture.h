#pragma once
#include <wrl/client.h>

#include <string>
#include <d2d1.h>

#include "Math/MathTypes.h"

class UITexture
{
public:
    UITexture();
    virtual ~UITexture() = default;

    virtual bool Load(class WindowsWindow* window, const std::wstring& kFileName);

    inline Microsoft::WRL::ComPtr<ID2D1Bitmap> GetTexture() const { return bitmap_; }
    
    inline MathTypes::uint32 GetWidth() const { return width_; }
    inline MathTypes::uint32 GetHeight() const { return height_; }

private:
    Microsoft::WRL::ComPtr<ID2D1Bitmap> bitmap_;
    
    MathTypes::uint32 width_;
    MathTypes::uint32 height_;
    
};
