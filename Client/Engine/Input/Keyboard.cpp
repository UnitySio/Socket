﻿#include "pch.h"
#include "Keyboard.h"

#include <ranges>

#include "UI/Canvas.h"

Keyboard::Keyboard() :
	key_states_(),
	key_events_()
{
}

void Keyboard::Begin()
{
	std::lock_guard<std::mutex> lock(mutex_);
	
	while (!key_events_.empty())
	{
		KeyEvent& event = key_events_.front();
		key_events_.pop();

		KeyboardEventType type = event.state;

		if (type == KeyboardEventType::kDown || type == KeyboardEventType::kUp)
		{
			WORD key_code = event.key_code;
			
			auto it = key_states_.find(key_code);
			if (it != key_states_.end())
			{
				KeyState& key_state = it->second;
				key_state.is_down = type == KeyboardEventType::kDown;
			}
		}
	}
}

void Keyboard::End()
{
	for (auto& key_state : key_states_ | std::views::values)
	{
		key_state.was_down = key_state.is_down;
	}
}

void Keyboard::Clear()
{
	std::lock_guard<std::mutex> lock(mutex_);
	
	while (!key_events_.empty())
	{
		key_events_.pop();
	}

	for (auto& key_state : key_states_ | std::views::values)
	{
		key_state.is_down = false;
		key_state.was_down = false;
	}
}

bool Keyboard::GetKey(WORD key_code)
{
	KeyState& key_state = key_states_[key_code];
	return key_state.is_down;
}

bool Keyboard::GetKeyDown(WORD key_code)
{
	KeyState& key_state = key_states_[key_code];
	return key_state.is_down && !key_state.was_down;
}

bool Keyboard::GetKeyUp(WORD key_code)
{
	KeyState& key_state = key_states_[key_code];
	return !key_state.is_down && key_state.was_down;
}

bool Keyboard::ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result)
{
	if (message == WM_KEYDOWN || message == WM_SYSKEYDOWN ||
		message == WM_KEYUP || message == WM_SYSKEYUP)
	{
		WORD key_code = LOWORD(wParam);
		WORD key_flags = HIWORD(lParam);
        
		MathTypes::uint32 char_code =  MapVirtualKey(key_code, MAPVK_VK_TO_CHAR);

		bool is_released = (key_flags & KF_UP) == KF_UP;
		bool is_repeat = (key_flags & KF_REPEAT) == KF_REPEAT;
        
		if (!is_released) return OnKeyDown(key_code, char_code,is_repeat);
		return OnKeyUp(key_code, char_code);
	}
    
	return false;
}

bool Keyboard::OnKeyDown(WORD key_code, MathTypes::uint32 char_code, bool is_repeat)
{
	OnInputKey(key_code, KeyboardEventType::kDown);
	return true;
}

bool Keyboard::OnKeyUp(WORD key_code, MathTypes::uint32 char_code)
{
	OnInputKey(key_code, KeyboardEventType::kUp);
	return true;
}

void Keyboard::OnInputKey(WORD key_code, KeyboardEventType state)
{
	std::lock_guard<std::mutex> lock(mutex_);
	
	KeyEvent event;
	event.state = state;
	event.key_code = key_code;

	key_events_.push(event);
}