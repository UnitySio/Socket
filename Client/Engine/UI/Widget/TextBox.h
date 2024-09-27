#pragma once
#include "Math/Color.h"
#include "UI/Widget.h"

namespace UI
{
    class TextBox : public Widget
    {
    public:
        TextBox(const std::wstring& kName);
        virtual ~TextBox() override = default;

        virtual void Tick(float delta_time) override;
        virtual void Render() override;

    private:
        std::wstring text_;
        
        int cursor_position_;

        float elapsed_;

        bool show_cursor_;

        std::vector<float> advances_;
        
    };
}
