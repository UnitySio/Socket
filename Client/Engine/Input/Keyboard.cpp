#include "pch.h"
#include "Keyboard.h"

#include <ranges>

Keyboard::Keyboard() : input_string_(), key_states_(), key_events_()
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

		if (type == KeyboardEventType::kPressed || type == KeyboardEventType::kReleased)
		{
			WORD key_code = event.key_code;
			
			auto it = key_states_.find(key_code);
			if (it != key_states_.end())
			{
				KeyState& key_state = it->second;
				key_state.is_down = type == KeyboardEventType::kPressed;
			}
		}
		else if (type == KeyboardEventType::kChar)
		{
			input_string_.push_back(event.character);
		}
	}
}

void Keyboard::End()
{
	input_string_.clear();
	
	for (auto& key_state : key_states_ | std::views::values)
	{
		key_state.was_down = key_state.is_down;
	}
}

void Keyboard::Clear()
{
	std::lock_guard<std::mutex> lock(mutex_);
	
	input_string_.clear();
	
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

bool Keyboard::IsKeyDown(WORD key_code)
{
	KeyState& key_state = key_states_[key_code];
	return key_state.is_down && key_state.was_down;
}

bool Keyboard::IsKeyPressed(WORD key_code)
{
	KeyState& key_state = key_states_[key_code];
	return key_state.is_down && !key_state.was_down;
}

bool Keyboard::IsKeyReleased(WORD key_code)
{
	KeyState& key_state = key_states_[key_code];
	return !key_state.is_down && key_state.was_down;
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
		const WCHAR kCharacter = static_cast<WCHAR>(wParam);
		return OnKeyChar(kCharacter);
	}
    
	return false;
}

bool Keyboard::OnKeyDown(WORD key_code, MathTypes::uint32 char_code)
{
	OnInputKey(key_code, KeyboardEventType::kPressed);

	KeyEvent event;
	event.state = KeyboardEventType::kPressed;
	event.key_code = key_code;
	command_buffer_.push(event);

	return true;
}

bool Keyboard::OnKeyUp(WORD key_code, MathTypes::uint32 char_code)
{
	OnInputKey(key_code, KeyboardEventType::kReleased);
	return true;
}

bool Keyboard::OnKeyChar(WCHAR character)
{
	std::lock_guard<std::mutex> lock(mutex_);

	KeyEvent event;
	event.state = KeyboardEventType::kChar;
	event.character = character;

	key_events_.push(event);
	
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