#pragma once
#include "UIBase.h"

namespace UI
{
    class Slider : public UIBase
    {
    public:
        Slider(const std::wstring& kName);
        virtual ~Slider() override = default;

        virtual void Tick(float deltaTime) override;
        virtual void Render() override;

    private:
        int value_;
        int min_value_;
        int max_value_;
    
    };
}
