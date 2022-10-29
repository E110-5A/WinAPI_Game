#pragma once
#include "Common.h"

namespace js
{

	class Time
	{
	public:
		static void Initialize();
		static void Tick();
		static void Render(HDC _dc);

		static float GetDeltaTime() { return mDeltaTime; }

	private:
		static LARGE_INTEGER m_CpuFrequency;
		static LARGE_INTEGER m_PrevFrequency;
		static LARGE_INTEGER m_CurFrequency;

		static float mDeltaTime;
		static float mTime;
	};


}