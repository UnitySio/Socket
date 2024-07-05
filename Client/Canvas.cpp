#include "Canvas.h"
#include "UIBase.h"
#include "BoxComponent.h"
#include "Windows/WindowsWindow.h"
#include "StringComponent.h"
#include "Button.h"
#include "ProgressBar.h"


Canvas::Canvas()
{
}

void Canvas::Render(WindowsWindow* kWindow)
{
	for (const auto& temp : renderList_)
	{
		if (temp->IsEnalbed())
			temp->Tick();
		if(temp->IsVisible())
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
	return static_cast<StringComponent*>(renderList_.back().get());
}

ProgressBar* Canvas::CreateProgressBar()
{
	std::shared_ptr<ProgressBar> bar = std::make_shared<ProgressBar>();
	renderList_.push_back(bar);
	return static_cast<ProgressBar*>(renderList_.back().get());
}

bool Canvas::ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result)
{
	message_ = message;
	messages_.push_back(message);
	return false;
}

