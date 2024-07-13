#include "Keyboard.h"

#include <ranges>

#include "Logger/Logger.h"

Keyboard::Keyboard() : key_states_(), key_events_()
{
	key_states_[VK_RIGHT] = KeyState();
	key_states_[VK_LEFT] = KeyState();
	key_states_['C'] = KeyState();
	key_states_['Z'] = KeyState();
}

void Keyboard::Begin()
{
	std::lock_guard<std::mutex> lock(mutex_);
	
	while (!key_events_.empty())
	{
		KeyEvent event = key_events_.front();
		key_events_.pop();

		WORD key_code = event.key_code;
		InputState state = event.state;

		KeyState& key_state = key_states_[key_code];
		key_state.is_down = state == InputState::kPressed || state == InputState::kRepeat;
	}
}

void Keyboard::End()
{
	for (auto it = key_states_.begin(); it != key_states_.end(); ++it)
	{
		KeyState& key_state = it->second;
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

	for (auto it = key_states_.begin(); it != key_states_.end(); ++it)
	{
		KeyState& key_state = it->second;
		key_state.is_down = false;
		key_state.was_down = false;
	}
}

bool Keyboard::IsKeyDown(WORD key_code) const
{
	return key_states_.at(key_code).is_down && key_states_.at(key_code).was_down;
}

bool Keyboard::IsKeyPressed(WORD key_code) const
{
	return key_states_.at(key_code).is_down && !key_states_.at(key_code).was_down;
}

bool Keyboard::IsKeyReleased(WORD key_code) const
{
	return !key_states_.at(key_code).is_down && key_states_.at(key_code).was_down;
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
		bool is_repeat = (key_flags & KF_REPEAT) == KF_REPEAT;
        
		if (!is_released) return OnKeyDown(key_code, char_code, is_repeat);
		return OnKeyUp(key_code, char_code);
	}

	if (message == WM_CHAR)
	{
		const WCHAR character = static_cast<WCHAR>(wParam);
		return OnKeyChar(character);
	}
    
	return false;
}

bool Keyboard::OnKeyDown(WORD key_code, MathTypes::uint32 char_code, bool is_repeat)
{
	OnInputKey(key_code, is_repeat ? InputState::kRepeat : InputState::kPressed);
	return true;
}

bool Keyboard::OnKeyUp(WORD key_code, MathTypes::uint32 char_code)
{
	OnInputKey(key_code, InputState::kReleased);
	return true;
}

bool Keyboard::OnKeyChar(WCHAR character)
{
	return true;
}

void Keyboard::OnInputKey(WORD key_code, InputState state)
{
	std::lock_guard<std::mutex> lock(mutex_);
	
	KeyEvent event;
	event.state = state;
	event.key_code = key_code;

	key_events_.push(event);
}