#include "jsTime.h"
#include "jsApplication.h"

namespace js
{
	LARGE_INTEGER Time::m_CpuFrequency;
	LARGE_INTEGER Time::m_PrevFrequency;
	LARGE_INTEGER Time::m_CurFrequency;
	float Time::mDeltaTime = 0.f;
	float Time::mTime = 0.f;

	void Time::Initialize()
	{
		QueryPerformanceFrequency(&m_CpuFrequency);

		QueryPerformanceCounter(&m_PrevFrequency);
	}
	void Time::Tick()
	{
		QueryPerformanceCounter(&m_CurFrequency);

		float fFrequencyGab
			= static_cast<float>(m_CurFrequency.QuadPart - m_PrevFrequency.QuadPart);

		mDeltaTime = fFrequencyGab / static_cast<float>(m_CpuFrequency.QuadPart);
		m_PrevFrequency.QuadPart = m_CurFrequency.QuadPart;
	}
	void Time::Render(HDC _dc)
	{
		mTime += GetDeltaTime();

		wchar_t szFloat[30] = {};
		if (1.0f < mTime)
		{
			float fps = 1.0f / mDeltaTime;
			swprintf_s(szFloat, 30, L"MyGame! fps : %f", fps);
			HWND hWnd = Application::GetInstance().GetWindowData().hWnd;
			SetWindowText(hWnd, szFloat);

			mTime = 0.f;
		}
	}
}