#pragma once
#include "UIBase.h"

class BoxComponent : public UIBase
{
public:
	BoxComponent();
	void SetFill(const bool& flag);
protected:
	virtual void Render(WindowsWindow* kWindow = World::Get()->GetWindow()) override;

private:
	void SetValue(const float value);

	bool isFilled_;
	float value_;
	friend class Button;
	friend class ProgressBar;
};

