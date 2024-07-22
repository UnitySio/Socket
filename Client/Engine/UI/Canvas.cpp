#include "pch.h"
#include "Canvas.h"

#include "UIBase.h"

Canvas::Canvas() :
    uis_()
{
}

void Canvas::AddUI(const std::shared_ptr<UIBase>& kUI)
{
    uis_.push_back(kUI);
}

void Canvas::Render()
{
    for (const auto& ui : uis_)
    {
        ui->Render();
    }
}
