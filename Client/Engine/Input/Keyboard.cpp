#include "pch.h"
#include "Keyboard.h"

#include <ranges>

#include "Logger/Logger.h"

Keyboard::Keyboard() : key_states_(), key_events_()
{
	RegisterKey(VK_LEFT);
	RegisterKey(VK_RIGHT);
	RegisterKey('Z');
	RegisterKey('C');
	RegisterKey(VK_F1);
	RegisterKey(VK_F2);
}

void Keyboard::Begin()
{
	std::lock_guard<std::mutex> lock(mutex_);
	
	while (!key_events_.empty())
	{
		KeyEvent& event = key_events_.front();
		key_events_.pop();

		WORD key_code = event.key_code;
		KeyboardEventType type = event.state;

		auto it = key_states_.find(key_code);
		if (it != key_states_.end())
		{
			KeyState& key_state = it->second;
			key_state.is_down = type == KeyboardEventType::kPressed;
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

void Keyboard::RegisterKey(WORD key_code)
{
	std::lock_guard<std::mutex> lock(mutex_);
	
	key_states_[key_code] = KeyState();
}

bool Keyboard::IsKeyDown(WORD key_code) const
{
	auto it = key_states_.find(key_code);
	if (it != key_states_.end())
	{
		return it->second.is_down && it->second.was_down;
	}
	
	return false;
}

bool Keyboard::IsKeyPressed(WORD key_code) const
{
	auto it = key_states_.find(key_code);
	if (it != key_states_.end())
	{
		return it->second.is_down && !it->second.was_down;
	}
	
	return false;
}

bool Keyboard::IsKeyReleased(WORD key_code) const
{
	auto it = key_states_.find(key_code);
	if (it != key_states_.end())
	{
		return !it->second.is_down && it->second.was_down;
	}
	
	return false;
}

bool Keyboard::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result)
{
	if (message == WM_KEYDOWN || message == WM_SYSKEYDOWN ||
		message == WM_KEYUP || message == WM_SYSKEYUP)
	{
		WORD key_code = LOWORD(wParam);
		WORD key_flags = HIWORD(lParam);
        
		MathTypes::uint32 char_code =  MapVirtualKey(key_code, MAPVK_VK_TO_CHAR);

		bool is_released = (key_flags & KF_UP) == KF_UP;
        
		if (!is_released) return OnKeyDown(key_code, char_code);
		return OnKeyUp(key_code, char_code);
	}

	if (message == WM_CHAR)
	{
		const WCHAR character = static_cast<WCHAR>(wParam);
		return OnKeyChar(character);
	}
    
	return false;
}

bool Keyboard::OnKeyDown(WORD key_code, MathTypes::uint32 char_code)
{
	OnInputKey(key_code, KeyboardEventType::kPressed);
	return true;
}

bool Keyboard::OnKeyUp(WORD key_code, MathTypes::uint32 char_code)
{
	OnInputKey(key_code, KeyboardEventType::kReleased);
	return true;
}

bool Keyboard::OnKeyChar(WCHAR character)
{
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