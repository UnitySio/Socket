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
	//const UINT& GetMsg() { return message_; }
	const std::vector<UINT> GetMsg() 
	{ 
		/*if (messages_.empty())
			return NULL;
		auto temp = messages_.back(); 
		messages_.clear();
		return temp;*/
		
		/*auto temp = messages_;
		messages_.clear();
		return temp;*/

		return messages_;
	}

	void ClearMsg() { messages_.clear(); }
private:
	UINT message_;
	std::vector<std::shared_ptr<UIBase>> renderList_;

	std::vector<UINT> messages_;
};

