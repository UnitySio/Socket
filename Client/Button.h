#pragma once
#include "UIBase.h"
#include <memory>

class BoxComponent;
class StringComponent;

class Button : public UIBase
{
public:
	Button();
	void SetText(const std::wstring& kString);
	void SetBoxSize(const Math::Vector2& size);
	
protected:
	virtual void Render(WindowsWindow* kWindow = World::Get()->GetWindow()) override;


private:
	std::shared_ptr<BoxComponent> box_;
	std::shared_ptr<StringComponent> string_;
};