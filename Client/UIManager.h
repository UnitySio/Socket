#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>
#include "Level/World.h"

class UIBase;
class Button;
class WindowsWindow;
class StringComponent;

class UIManager : public Singleton<UIManager>
{
public:
	void Render(WindowsWindow* kWindow = World::Get()->GetWindow());
	std::shared_ptr<UIBase> CreateButton();
	StringComponent* CreateString();


private:
	std::vector<std::shared_ptr<UIBase>> renderList_;
};

