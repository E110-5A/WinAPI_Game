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

		virtual void Initialize();	// ���� ���ʷ� ������ �� ȣ��
		virtual void Tick();
		virtual void Render(HDC _dc);

		virtual void Enter() {}		// �ش� ������ ����� �� ȣ��
		virtual void Exit() {}

		void AddGameObject(GameObject* _obj);

	private:
		std::vector<GameObject*> m_GameObj;
	};


}