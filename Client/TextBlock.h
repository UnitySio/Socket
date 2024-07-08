#pragma once
#include "UIBase.h"
#include <memory>

class StringComponent;

class TextBlock : public UIBase
{
public:
	TextBlock();
	void SetText(const std::wstring& kString);
	void SetSize(const Math::Vector2& kSize);

protected:
	virtual void Render(WindowsWindow* kWindow = World::Get()->GetWindow()) override;
	virtual void Tick() override;

private:
	std::shared_ptr<StringComponent> str_;
};

