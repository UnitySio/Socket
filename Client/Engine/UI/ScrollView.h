#pragma once
#include "UIBase.h"
#include <memory>

class BoxComponent;

class ScrollView : public UIBase
{
public:
	ScrollView();

protected:
	virtual void Render(WindowsWindow* kWindow = World::Get()->GetWindow()) override;
	virtual void Tick() override;

private:
	std::shared_ptr<BoxComponent> outer_;
	std::shared_ptr<BoxComponent> inner_;
	POINT prevPos_;
	bool isVertical_;
	float value_;
	bool touchable_;
};

