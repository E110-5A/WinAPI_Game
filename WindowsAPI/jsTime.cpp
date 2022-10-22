#include "jsTime.h"

namespace js
{
	LARGE_INTEGER jsTime::m_CpuFrequency;
	LARGE_INTEGER jsTime::m_PrevFrequency;
	LARGE_INTEGER jsTime::m_CurFrequency;
	float jsTime::m_DeltaTime = 0.f;

	void jsTime::Initialize()
	{
		QueryPerformanceFrequency(&m_CpuFrequency);

		QueryPerformanceCounter(&m_PrevFrequency);
	}
	void jsTime::Tick()
	{
		QueryPerformanceCounter(&m_CurFrequency);

		float fFrequencyGab
			= static_cast<float>(m_CurFrequency.QuadPart - m_PrevFrequency.QuadPart);

		m_DeltaTime = fFrequencyGab / static_cast<float>(m_CpuFrequency.QuadPart);
		m_PrevFrequency.QuadPart = m_CurFrequency.QuadPart;
	}
	void jsTime::Render(HDC _dc)
	{
		wchar_t szFloat[30] = {};

		float fps = 1.0f / m_DeltaTime;
		swprintf_s(szFloat, 30, L"fps : %f", fps);
		size_t strLen = wcsnlen_s(szFloat, 30);
		TextOut(_dc, 10, 10, szFloat, (int)strLen);
	}
}