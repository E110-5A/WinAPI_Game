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

		static void ChangeScene(eSceneType type);
		static Scene* GetCurScene() { return mCurScene; }
		
	private:
		static Scene* mScene[(UINT)eSceneType::End];
		static Scene* mCurScene;
	};


}