#include "jsInput.h"

namespace js
{
	int ASCII[(UINT)eKeyCode::END] =
	{
		'Q','W','E','R','T','Y','U','I','O','P',
		'A','S','D','F','G','H','J','K','L',
		'Z','X','C','V','B','N','M',

		VK_RETURN, VK_ESCAPE, VK_LSHIFT, VK_LMENU, VK_LCONTROL,
		VK_SPACE, VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN,
		VK_LBUTTON, VK_RBUTTON,

		VK_NUMPAD0,
		VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3,
		VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6,
		VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9,

		'0','1','2','3','4','5','6','7','8','9',
	};
	std::vector<jsInput::Key> jsInput::m_Keys;

	void jsInput::Initialize()
	{
		for (size_t idx = 0; idx < (UINT)eKeyCode::END; idx++)
		{
			Key key = { (eKeyCode)idx, eKeyState::NONE, false };

			m_Keys.push_back(key);
		}
	}
	void jsInput::Tick()
	{
		for (size_t idx = 0; idx < (UINT)eKeyCode::END; idx++)
		{
			// 키가 눌린 경우
			if (GetAsyncKeyState(ASCII[idx]) & 0x8000)
			{
				// 이전에 눌렸음
				if (m_Keys[idx].bPressed)
				{
					m_Keys[idx].state = eKeyState::PRESSED;
				}
				else
				{
					m_Keys[idx].state = eKeyState::DOWN;
				}
				m_Keys[idx].bPressed = true;
			}
			// 키가 눌리지 않은 경우
			else
			{
				// 이전에 눌렸음
				if (m_Keys[idx].bPressed)
				{
					m_Keys[idx].state = eKeyState::UP;
				}
				else
				{
					m_Keys[idx].state = eKeyState::NONE;
				}
				m_Keys[idx].bPressed = false;
			}
		}
	}
	void jsInput::Render(HDC _dc)
	{
	}
	eKeyState jsInput::GetKeyState(eKeyCode _KeyCode)
	{
		return m_Keys[(UINT)_KeyCode].state;
	}
}