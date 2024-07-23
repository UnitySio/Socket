#pragma once
#include "UIBase.h"

namespace UI
{
    class Button : public UIBase
    {
    public:
        Button(const std::wstring& kName);
        virtual ~Button() override = default;
        
    protected:
        virtual void Tick(float deltaTime) override;
        virtual void Render() override;
    };
}
