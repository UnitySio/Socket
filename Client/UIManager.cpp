#include "UIManager.h"
#include "UIBase.h"
#include "BoxComponent.h"
#include "Windows/WindowsWindow.h"
#include "StringComponent.h"


void UIManager::Render(WindowsWindow* kWindow)
{
	for (const auto& temp : renderList_)
	{
		temp->Render(kWindow);
	}
}

std::shared_ptr<UIBase> UIManager::CreateButton()
{
	std::shared_ptr<BoxComponent> button = std::make_shared<BoxComponent>();
	renderList_.push_back(button);
	return renderList_.back();
	
}

StringComponent* UIManager::CreateString()
{
	std::shared_ptr<StringComponent> string = std::make_shared<StringComponent>();
	renderList_.push_back(string);
	std::shared_ptr<UIBase> temp = renderList_.back();
	return static_cast<StringComponent*>(temp.get());
}
