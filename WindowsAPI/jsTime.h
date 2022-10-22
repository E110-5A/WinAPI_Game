#pragma once
#include "Common.h"

namespace js
{

	class jsTime
	{
	public:
		static void Initialize();
		static void Tick();
		static void Render(HDC _dc);

		static float GetDeltaTime() { return m_DeltaTime; }

	private:
		static LARGE_INTEGER m_CpuFrequency;
		static LARGE_INTEGER m_PrevFrequency;
		static LARGE_INTEGER m_CurFrequency;

		static float m_DeltaTime;
	};


}