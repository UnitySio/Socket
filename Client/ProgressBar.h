#pragma once
#include "UIBase.h"
#include <memory>

class BoxComponent;

class ProgressBar : public UIBase
{
public:
	ProgressBar();
	void SetValue(const float& value);
protected:
	virtual void Render(WindowsWindow* kWindow = World::Get()->GetWindow()) override;

private:
	std::shared_ptr<BoxComponent> outer_;
	std::shared_ptr<BoxComponent> inner_;
};