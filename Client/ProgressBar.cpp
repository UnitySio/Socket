#include "ProgressBar.h"
#include "BoxComponent.h"

ProgressBar::ProgressBar()
{
	outer_ = std::make_shared<BoxComponent>();
	inner_ = std::make_shared<BoxComponent>();
	inner_->SetFill(true);
	inner_->SetValue(0.0f);

	outer_->SetParent(this);
	inner_->SetParent(this);
}

void ProgressBar::SetValue(const float& value)
{
	inner_->SetValue(value);
}

void ProgressBar::Render(WindowsWindow* kWindow)
{
	Super::Render(kWindow);
	outer_->Render(kWindow);
	inner_->Render(kWindow);
}
