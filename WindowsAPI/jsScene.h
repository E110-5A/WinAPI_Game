#pragma once

#include "jsEntity.h"

namespace js
{
	class GameObject;
	class Scene :
		public Entity
	{
	public:
		Scene();
		virtual ~Scene();

		virtual void Initialize();	// 씬이 최초로 생성될 때 호출
		virtual void Tick();
		virtual void Render(HDC hdc);

		virtual void Enter();		// 해당 씬으로 변경될 때 호출
		virtual void Exit();

		virtual void PushBossUI() {}
		virtual void PopBossUI() {}

		void AddGameObject(GameObject* obj, eColliderLayer type);
		std::vector<GameObject*>& GetGameObjects(eColliderLayer type) { return mObjects[(UINT)type]; }
		std::vector<std::vector<GameObject*>>& GetGameObjects() { return mObjects; }


	private:
		std::vector<std::vector<GameObject*>> mObjects;
		WindowData mWindowInfo;
	};

	typedef std::vector<std::vector<GameObject*>> GameObjects;
	typedef std::vector<GameObject*>::iterator LayerObjects;

}