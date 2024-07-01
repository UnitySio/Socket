#include "UIManager.h"
#include "UIBase.h"
#include "Button.h"


void UIManager::Render()
{
	for (const auto& temp : renderList_)
	{
		temp->Render();
	}
}

std::shared_ptr<Button> UIManager::CreateButton()
{
	std::shared_ptr<Button> button = std::make_shared<Button>();
	button->SetSize(Math::Vector2(5, 5));
	renderList_.push_back(button);
	return button;
}
