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
		virtual void Render(HDC _dc);

		virtual void Enter() {}		// 해당 씬으로 변경될 때 호출
		virtual void Exit() {}

		void AddGameObject(GameObject* _obj);

	private:
		std::vector<GameObject*> m_GameObj;
	};


}