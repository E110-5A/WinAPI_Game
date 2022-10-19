#include "jsApplication.h"

namespace js
{
	jsApplication jsApplication::m_Instance;

	jsApplication::jsApplication()
	{
		m_WindowData.clear();
	}

	jsApplication::~jsApplication()
	{
		ReleaseDC(m_WindowData.hWnd, m_WindowData.hdc);
	}

	void jsApplication::Initialize(WindowData _data)
	{
		m_WindowData = _data;
		m_WindowData.hdc = GetDC(_data.hWnd);
	}

	void jsApplication::Tick()
	{
	}
}

