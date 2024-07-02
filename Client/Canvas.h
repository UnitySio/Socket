#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>
#include "Level/World.h"

class UIBase;
class Button;
class WindowsWindow;
class StringComponent;

class Canvas : public Singleton<Canvas>
{
public:
	Canvas();
	void Render(WindowsWindow* kWindow = World::Get()->GetWindow());
	Button* CreateButton();
	StringComponent* CreateString();


private:
	std::vector<std::shared_ptr<UIBase>> renderList_;
};

