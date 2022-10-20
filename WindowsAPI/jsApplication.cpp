#include "jsApplication.h"
#include "jsSceneManager.h"

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
	}

	void jsApplication::Initialize(WindowData _data)
	{
		m_WindowData = _data;
		m_WindowData.hdc = GetDC(_data.hWnd);

		jsSceneManager::Initialize();
	}

	void jsApplication::Tick()
	{
		jsSceneManager::Tick();
		jsSceneManager::Render(m_WindowData.hdc);
	}
}

