#pragma once
#include "UIBase.h"
#include <memory>

class BoxComponent;

class ProgressBar : public UIBase
{
public:
	ProgressBar();
	void SetValue(const float& value);
	void SetTouchEnable(const bool& flag);
	void SetBoxSize(const Math::Vector2 size);

protected:
	virtual void Render(WindowsWindow* kWindow = World::Get()->GetWindow()) override;
	virtual void Tick() override;
private:
	bool touchable_;
	std::shared_ptr<BoxComponent> outer_;
	std::shared_ptr<BoxComponent> inner_;
};