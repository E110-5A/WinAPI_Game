#pragma once
#include "Common.h"

namespace js
{
	class Scene;
	class SceneManager
	{
	public:
		static void Initialize();
		static void Tick();
		static void Render(HDC _dc);
		static void Release();

		static Scene* GetCurScene() { return m_CurScene; }
		
	private:
		static Scene* m_Scene[(UINT)eSceneType::End];
		static Scene* m_CurScene;
	};


}