#pragma once
#include "UIBase.h"

class Button : public UIBase
{
public:
	Button();

protected:
	virtual void Render(WindowsWindow* kWindow = World::Get()->GetWindow()) override;

private:
};

