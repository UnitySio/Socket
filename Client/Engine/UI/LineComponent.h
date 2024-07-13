#pragma once
#include "UI/UIBase.h"
class LineComponent : public UIBase
{
public:
	LineComponent();

protected:
	virtual void Tick();
	virtual void Render(WindowsWindow* kWindow = World::Get()->GetWindow());

private:
	Math::Vector2 start_;
	Math::Vector2 end_;
	Math::Color color_;
	float stroke_;

};

