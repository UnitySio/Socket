#pragma once
#include "UIBase.h"
#include <memory>

class BoxComponent;
class ProgressBar;

class ScrollView : public UIBase
{
public:
	ScrollView();
	virtual void SetSize(const Math::Vector2& kSize) override;
	void SetEnableSideBar(const bool& kFlag);

protected:
	virtual void Render(WindowsWindow* kWindow = World::Get()->GetWindow()) override;
	virtual void Tick() override;

private:
	std::shared_ptr<BoxComponent> outer_;
	std::shared_ptr<BoxComponent> inner_;
	std::shared_ptr<ScrollView> sidebar_;

	POINT prevPos_;
	bool isVertical_;
	float value_;
	bool touchable_;
};

