#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>
#include "Level/World.h"
#include "UIBase.h"
#include <Windows.h>
#include <stack>

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
	bool ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result);
	const bool& IsDown() { return isDown_; }
	
private:
	bool isDown_;
	std::vector<std::shared_ptr<UIBase>> renderList_;
	std::vector<std::shared_ptr<UINT>> messages_;
};