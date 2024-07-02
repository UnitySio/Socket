#pragma once
#include "UIBase.h"

class BoxComponent : public UIBase
{
public:
	BoxComponent();

protected:
	virtual void Render(WindowsWindow* kWindow = World::Get()->GetWindow()) override;

private:
	friend class Button;
	
};

