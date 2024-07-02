#include "Canvas.h"
#include "UIBase.h"
#include "BoxComponent.h"
#include "Windows/WindowsWindow.h"
#include "StringComponent.h"
#include "Button.h"


Canvas::Canvas()
{
}

void Canvas::Render(WindowsWindow* kWindow)
{
	for (const auto& temp : renderList_)
	{
		temp->Render(kWindow);
	}
}

Button* Canvas::CreateButton()
{
	std::shared_ptr<Button> button = std::make_shared<Button>();
	renderList_.push_back(button);
	return static_cast<Button*>(renderList_.back().get());
	
}

StringComponent* Canvas::CreateString()
{
	std::shared_ptr<StringComponent> string = std::make_shared<StringComponent>();
	renderList_.push_back(string);
	std::shared_ptr<UIBase> temp = renderList_.back();
	return static_cast<StringComponent*>(temp.get());
}
