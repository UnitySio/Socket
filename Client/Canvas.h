#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>
#include "Level/World.h"
#include "UIBase.h"
#include <Windows.h>

class Button;
class WindowsWindow;
class StringComponent;
class ProgressBar;

class Canvas : public Singleton<Canvas>
{
public:
	Canvas();
	void Render(WindowsWindow* kWindow = World::Get()->GetWindow());
	Button* CreateButton();
	StringComponent* CreateString();
	ProgressBar* CreateProgressBar();


private:
	std::vector<std::shared_ptr<UIBase>> renderList_;
};

