#pragma once
#include "UIBase.h"
#include <memory>

class BoxComponent;

class ProgressBar : public UIBase
{
public:
	ProgressBar();
	void SetValue(const float& value);
	void SetBoxSize(const Math::Vector2 size);
	const bool& OnMouse();
	void SetTouchEnable(const bool& flag);
	void SetVertical(const bool& flag);

protected:
	virtual void Render(WindowsWindow* kWindow = World::Get()->GetWindow()) override;
	virtual void Tick() override;

private:
	float value_;
	bool onMouse_;
	bool touchable_;
	bool isDown_;
	bool isVertical_;
	std::shared_ptr<BoxComponent> outer_;
	std::shared_ptr<BoxComponent> inner_;
};