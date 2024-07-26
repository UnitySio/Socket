#pragma once
#include "UI/Widget.h"

namespace UI
{
    class Image : public Widget
    {
    public:
        Image(const std::wstring& kName);
        virtual ~Image() override = default;

    protected:
        virtual void Render() override;
    };
}
