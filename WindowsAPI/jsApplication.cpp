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
	}

	void jsApplication::Initialize(WindowData _data)
	{
		m_WindowData = _data;
		m_WindowData.hdc = GetDC(_data.hWnd);

		jsTime::Initialize();
		jsInput::Initialize();
		jsSceneManager::Initialize();
	}

	void jsApplication::Tick()
	{
		jsTime::Tick();
		jsInput::Tick();

		jsSceneManager::Tick();
		jsSceneManager::Render(m_WindowData.hdc);
		
		jsInput::Render(m_WindowData.hdc);
		jsTime::Render(m_WindowData.hdc);
	}
}

