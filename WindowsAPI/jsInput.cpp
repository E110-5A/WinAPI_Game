#include "jsInput.h"
#include "jsApplication.h"

#include "jsCamera.h"

namespace js
{
	Vector2 Input::mMousePos = Vector2::Zero;
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
	std::vector<Input::Key> Input::mKeys;

	void Input::Initialize()
	{
		for (size_t idx = 0; idx < (UINT)eKeyCode::END; idx++)
		{
			Key key = { (eKeyCode)idx, eKeyState::NONE, false };

			mKeys.push_back(key);
		}
	}
	void Input::Tick()
	{
		if (GetFocus())
		{
			// 키보드
			for (size_t idx = 0; idx < (UINT)eKeyCode::END; idx++)
			{
				// 키가 눌린 경우
				if (GetAsyncKeyState(ASCII[idx]) & 0x8000)
				{
					// 이전에 눌렸음
					if (mKeys[idx].bPressed)
					{
						mKeys[idx].state = eKeyState::PRESSED;
					}
					else
					{
						mKeys[idx].state = eKeyState::DOWN;
					}
					mKeys[idx].bPressed = true;
				}
				// 키가 눌리지 않은 경우
				else
				{
					// 이전에 눌렸음
					if (mKeys[idx].bPressed)
					{
						mKeys[idx].state = eKeyState::UP;
					}
					else
					{
						mKeys[idx].state = eKeyState::NONE;
					}
					mKeys[idx].bPressed = false;
				}
			}
			
			// 마우스
			POINT mousePos = {};
			GetCursorPos(&mousePos);
			HWND hwnd = Application::GetInstance().GetWindowData().hWnd;
			ScreenToClient(hwnd, &mousePos);
			mMousePos.x = mousePos.x;
			mMousePos.y = mousePos.y;
		}
		else
		{
			for (UINT idx = 0; idx < (UINT)eKeyCode::END; ++idx)
			{
				if (eKeyState::DOWN == mKeys[idx].state
					|| eKeyState::PRESSED == mKeys[idx].state)
					mKeys[idx].state = eKeyState::UP;
				else if (eKeyState::UP == mKeys[idx].state)
					mKeys[idx].state = eKeyState::NONE;
			}
		}
	}

	void Input::Render(HDC hdc)
	{
		/*wchar_t szFloat[40] = {};
		Vector2 mousePos = Camera::CalculateMousePos(mMousePos);
		std::wstring stateStr = L"Mouse Posision :";
		stateStr += L" (";
		stateStr += std::to_wstring((int)mousePos.x);
		stateStr += L" , ";
		stateStr += std::to_wstring((int)mousePos.y);
		stateStr += L")";

		swprintf_s(szFloat, 40, stateStr.c_str());
		int strLen = wcsnlen_s(szFloat, 40);
		TextOut(hdc, 10, 60, szFloat, strLen);*/
	}


	eKeyState Input::GetKeyState(eKeyCode _KeyCode)
	{
		return mKeys[(UINT)_KeyCode].state;
	}
	Vector2 Input::GetMousePos(HWND hWnd)
	{
		Pos vMousePos(-1.f,-1.f);
		if (GetFocus())
		{
			// 마우스
			POINT mousePos = {};
			GetCursorPos(&mousePos);
			ScreenToClient(hWnd, &mousePos);
			vMousePos.x = mousePos.x;
			vMousePos.y = mousePos.y;

			return vMousePos;
		}
		return vMousePos;
	}
}