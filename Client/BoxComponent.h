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
	void SetVertical(const bool& flag);
	void SetInnerScroll(const bool& flag)
	{
		isInnerScroll_ = flag;
	}

	std::shared_ptr<BoxComponent> outer_;

	bool isInnerScroll_;
	bool isVertical_;
	bool isFilled_;
	float value_;
	friend class Button;
	friend class ProgressBar;
	friend class ScrollView;
};

