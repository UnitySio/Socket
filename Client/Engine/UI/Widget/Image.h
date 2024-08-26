#pragma once
#include <memory>

#include "UI/Widget.h"

class UITexture;

namespace UI
{
    class Image : public Widget
    {
    public:
        Image(const std::wstring& kName);
        virtual ~Image() override = default;

        inline void SetTexture(UITexture* texture) { texture_ = texture; }

    protected:
        virtual void Render() override;

    private:
        UITexture* texture_;
        
    };
}
