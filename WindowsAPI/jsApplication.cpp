#include "jsApplication.h"
#include "jsSceneManager.h"
#include "jsTime.h"
#include "jsInput.h"
namespace js
{
	jsApplication::jsApplication()
	{
		m_WindowData.clear();
	}

	jsApplication::~jsApplication()
	{
		jsSceneManager::Release();
		ReleaseDC(m_WindowData.hWnd, m_WindowData.hdc);
		ReleaseDC(m_WindowData.hWnd, m_WindowData.backBuffer);
	}

	void jsApplication::InitializeWindow(WindowData _data)
	{
		m_WindowData = _data;
		m_WindowData.hdc = GetDC(_data.hWnd);

		RECT rect = { 0,0,m_WindowData.width, m_WindowData.height };
		AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

		SetWindowPos(m_WindowData.hWnd, nullptr, 0, 0
			, rect.right - rect.left, rect.bottom - rect.top, 0);

		ShowWindow(m_WindowData.hWnd, true);


		m_WindowData.backTexture 
			= CreateCompatibleBitmap(m_WindowData.hdc, m_WindowData.width, m_WindowData.height);

		m_WindowData.backBuffer
			= CreateCompatibleDC(m_WindowData.hdc);
		HBITMAP defaultBitMap
			= (HBITMAP)SelectObject(m_WindowData.backBuffer, m_WindowData.backTexture);

		DeleteObject(defaultBitMap);
	}

	void jsApplication::Initialize(WindowData _data)
	{
		InitializeWindow(_data);


		jsTime::Initialize();
		jsInput::Initialize();
		jsSceneManager::Initialize();
	}

	void jsApplication::Tick()
	{
		jsTime::Tick();
		jsInput::Tick();
		jsSceneManager::Tick();

		Rectangle(m_WindowData.backBuffer, -1, -1, m_WindowData.width + 1, m_WindowData.height + 1);

		jsSceneManager::Render(m_WindowData.backBuffer);
		jsInput::Render(m_WindowData.backBuffer);
		jsTime::Render(m_WindowData.backBuffer);

		BitBlt(m_WindowData.hdc, 0, 0, m_WindowData.width, m_WindowData.height,
			m_WindowData.backBuffer, 0, 0, SRCCOPY);
	}
}

