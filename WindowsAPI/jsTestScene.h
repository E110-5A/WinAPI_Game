#pragma once
#include "jsScene.h"

namespace js
{
	class PlayerProjectile;
	class ItemObject;
	class TestScene : public Scene
	{
	public:
		TestScene();
		~TestScene();

		void Initialize() override;

		void TileLoadTest();
		void BGTest();
		void ObjectTest();
		void SetLayer();
		void SetUI();

		void Tick() override;
		void Render(HDC hdc) override;


		virtual void Enter();
		virtual void Exit();

	private:
		PlayerProjectile*	mPlayerAttack[PLAYER_PROJECTILE_POOL];
	};
}
