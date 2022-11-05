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
		static void DestroyGameObject();
		static void Release();

		static void ChangeScene(eSceneType type);
		static Scene* GetCurScene() { return mCurScene; }
		static void SetCurScene(Scene* curScene) { mCurScene = curScene; }


	private:
		static Scene* mScene[(UINT)eSceneType::End];
		static Scene* mCurScene;
	};


}