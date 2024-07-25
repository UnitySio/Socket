#pragma once
#include "UIBase.h"

namespace UI
{
    class ScrollBox : public UIBase
    {
    public:
        ScrollBox(const std::wstring& kName);
        virtual ~ScrollBox() override = default;

    protected:
        virtual void Tick(float deltaTime) override;
        virtual void Render() override;
    };
}
