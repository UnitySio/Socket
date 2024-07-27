#include "pch.h"
#include "Canvas.h"

#include "Widget.h"

Canvas::Canvas() :
    width_(0.f),
    height_(0.f),
    reference_resolution_width_(ProjectSettings::kCanvasReferenceWidth),
    reference_resolution_height_(ProjectSettings::kCanvasReferenceHeight),
    match_mode_(ProjectSettings::kMatchMode),
    uis_()
{
}

void Canvas::AddWidget(const std::shared_ptr<Widget>& kWidget)
{
    uis_.push_back(kWidget);
}

float Canvas::GetScaleRatio() const
{
    const float width_ratio = width_ / static_cast<float>(reference_resolution_width_);
    const float height_ratio = height_ / static_cast<float>(reference_resolution_height_);

    return width_ratio * (1.f - match_mode_) + height_ratio * match_mode_;
}

void Canvas::OnResize(MathTypes::uint32 width, MathTypes::uint32 height)
{
    width_ = width;
    height_ = height;

    for (const auto& ui : uis_)
    {
        ui->UpdateRect();
    }
}

void Canvas::Render()
{
    for (const auto& ui : uis_)
    {
        ui->Render();
    }
}

void Canvas::Clear()
{
    uis_.clear();
}
