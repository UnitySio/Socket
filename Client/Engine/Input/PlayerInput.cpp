#include "pch.h"
#include "PlayerInput.h"

#include <ranges>

#include "UI/Canvas.h"

PlayerInput::PlayerInput() :
	key_states_()
{
}

void PlayerInput::UpdateKeyStates()
{
	for (auto& key_state : key_states_ | std::views::values)
	{
		key_state.was_down = key_state.is_down;
	}
}

void PlayerInput::Clear()
{
	std::lock_guard<std::mutex> lock(mutex_);

	for (auto& key_state : key_states_ | std::views::values)
	{
		key_state.is_down = false;
		key_state.was_down = false;
	}
}

bool PlayerInput::GetKey(WORD key_code)
{
	KeyState& key_state = key_states_[key_code];
	return key_state.is_down;
}

bool PlayerInput::GetKeyDown(WORD key_code)
{
	KeyState& key_state = key_states_[key_code];
	return key_state.is_down && !key_state.was_down;
}

bool PlayerInput::GetKeyUp(WORD key_code)
{
	KeyState& key_state = key_states_[key_code];
	return !key_state.is_down && key_state.was_down;
}

void PlayerInput::OnKeyEvent(const KeyEvnet& kEvent)
{
	const KeyAction& action = kEvent.action;

	if ((action == KeyAction::kPressed && !kEvent.is_repeat) ||
		action == KeyAction::kReleased)
	{
		WORD key_code = kEvent.key_code;
			
		auto it = key_states_.find(key_code);
		if (it != key_states_.end())
		{
			KeyState& key_state = it->second;
			key_state.is_down = action == KeyAction::kPressed;
		}
	}
}
