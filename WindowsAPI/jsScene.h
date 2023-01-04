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
		virtual void Render(HDC hdc);

		virtual void Enter();		// �ش� ������ ����� �� ȣ��
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