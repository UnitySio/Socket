#include "Canvas.h"
#include "UIBase.h"
#include "BoxComponent.h"
#include "Windows/WindowsWindow.h"
#include "StringComponent.h"
#include "Button.h"
#include "ProgressBar.h"
#include "ScrollView.h"
#include "TextBlock.h"
#include "Image.h"


Canvas::Canvas()
{
	isDown_ = false;
}

Canvas::~Canvas()
{
	renderList_.clear();
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

ProgressBar* Canvas::CreateProgressBar()
{
	std::shared_ptr<ProgressBar> bar = std::make_shared<ProgressBar>();
	renderList_.push_back(bar);
	return static_cast<ProgressBar*>(renderList_.back().get());
}

ScrollView* Canvas::CreateScrollView()
{
	std::shared_ptr<ScrollView> view = std::make_shared<ScrollView>();
	renderList_.push_back(view);
	return static_cast<ScrollView*>(renderList_.back().get());
}

TextBlock* Canvas::CreateTextBlock()
{
	std::shared_ptr<TextBlock> text = std::make_shared<TextBlock>();
	renderList_.push_back(text);
	return static_cast<TextBlock*>(renderList_.back().get());
}

Image* Canvas::CreateImage()
{
	std::shared_ptr<Image> image = std::make_shared<Image>();
	renderList_.push_back(image);
	return static_cast<Image*>(renderList_.back().get());
}

bool Canvas::ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result)
{
	if (message == WM_LBUTTONDOWN)
	{
		isDown_ = true;
	}

	else if (message == WM_LBUTTONUP)
	{
		isDown_ = false;
	}
	return false;
}

