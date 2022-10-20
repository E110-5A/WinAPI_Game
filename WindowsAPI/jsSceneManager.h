#pragma once
#include "Common.h"

namespace js
{
	class jsScene;
	class jsSceneManager
	{
	public:
		static void Initialize();
		static void Tick();
		static void Render(HDC _dc);
		static void Release();
		
	private:
		static jsScene* m_Scene[(UINT)eSceneType::END];
		static jsScene* m_CurScene;
	};


}