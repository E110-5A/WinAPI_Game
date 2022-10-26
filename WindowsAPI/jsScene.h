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

		virtual void Initialize();
		virtual void Tick();
		virtual void Render(HDC _dc);

		void AddGameObject(GameObject* _obj);

	private:
		std::vector<GameObject*> m_GameObj;
	};


}