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
		static Scene* GetPlayScene() { return mPlayScene; }
		static eSceneType GetPlaySceneType() { return mType; }
		static void SetPlayScene(Scene* playScene) { mPlayScene = playScene; }
		static Scene* GetScene(eSceneType type) { return mScene[(UINT)type]; }

		template <typename T>
		static void LoadMap(const std::wstring& path, eSceneType type)
		{
			js::Scene* scene = js::SceneManager::GetScene(type);
			T* toolScene = dynamic_cast<T*>(scene);
			toolScene->LoadTilePalette(path);
		}

	private:
		static Scene* mScene[(UINT)eSceneType::End];
		static Scene* mPlayScene;
		static eSceneType mType;
	};


}