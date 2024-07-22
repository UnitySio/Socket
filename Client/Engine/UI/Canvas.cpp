#include "pch.h"
#include "Canvas.h"

#include "UIBase.h"

Canvas::Canvas() :
    width_(0.f),
    height_(0.f),
    uis_()
{
}

void Canvas::AddUI(const std::shared_ptr<UIBase>& kUI)
{
    uis_.push_back(kUI);
}

void Canvas::OnResize(MathTypes::uint32 width, MathTypes::uint32 height)
{
    width_ = width;
    height_ = height;
}

void Canvas::Render()
{
    for (const auto& ui : uis_)
    {
        ui->Render();
    }
}
