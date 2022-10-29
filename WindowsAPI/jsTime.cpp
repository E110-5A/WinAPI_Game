#include "jsTime.h"

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
		wchar_t szFloat[30] = {};

		float fps = 1.0f / mDeltaTime;
		swprintf_s(szFloat, 30, L"fps : %f", fps);
		size_t strLen = wcsnlen_s(szFloat, 30);
		TextOut(_dc, 10, 10, szFloat, (int)strLen);
	}
}