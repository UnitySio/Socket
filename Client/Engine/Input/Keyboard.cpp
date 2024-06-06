#include "Keyboard.h"

Keyboard::Keyboard()
{
}

void Keyboard::RegisterKey(BYTE keycode)
{
	EventKeyboard* temp = new EventKeyboard(keycode, WM_KEYUP);
	keys_.push_back(std::move(*temp));
}

void Keyboard::UnRegisterKey(BYTE keycode)
{
	for (auto it = keys_.begin(); it != keys_.end(); ++it)
	{
		if (it->keyCode_ == keycode)
		{
			keys_.erase(it);
			break;
		}
	}
}

bool Keyboard::ProcessMessage(UINT message, WPARAM wParam, LPARAM lParam, MathTypes::uint32 handler_result)
{
	if (message == WM_KEYDOWN || message == WM_SYSKEYDOWN ||
		message == WM_KEYUP || message == WM_SYSKEYUP)
	{
		WORD key_code = LOWORD(wParam);
		WORD key_flags = HIWORD(lParam);
		WORD scan_code = LOBYTE(key_flags);

		for (auto it = keys_.begin(); it != keys_.end(); ++it)
		{
			if (it->keyCode_ == key_code)
			{
				if (message == WM_KEYDOWN)
				{
					if (it->keyState_ == EventKeyboard::KeyState::Down || it->keyState_ == EventKeyboard::KeyState::Pressing)
					{
						Pressing(*it);
						it->keyState_ = EventKeyboard::KeyState::Pressing;
						return true;
					}

					else if (it->keyState_ == EventKeyboard::KeyState::Up)
					{
						OnKeyDown(*it);
						it->keyState_ = EventKeyboard::KeyState::Down;
						return true;
					}
				}
				
				if (it->keyState_ == EventKeyboard::KeyState::Up)
					return true;
				OnKeyUp(*it);
				it->keyState_ = EventKeyboard::KeyState::Up;
				return true;

			}
		}
		return false;
	}
	return false;
	/*bool is_down = (key_flags & KF_UP) != KF_UP;
	if (is_down)
	{
		OnKeyDown();
	}
	else
	{
		OnKeyUp();
	}

	return true;
}

return false;*/
}

void Keyboard::OnKeyDown(const EventKeyboard& kE)
{
	OnDown.Execute(kE);
}

void Keyboard::OnKeyUp(const EventKeyboard& kE)
{
	OnUp.Execute(kE);
}

void Keyboard::Pressing(const EventKeyboard& kE)
{
	Pressed.Execute(kE);
}
