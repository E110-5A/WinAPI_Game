#pragma once
#include "jsScene.h"

namespace js
{
	class PlayerProjectile;
	class TestScene : public Scene
	{
	public:
		TestScene();
		~TestScene();

		void Initialize() override;

		void TileLoadTest();
		void BGTest();
		void ObjectTest();

		void Tick() override;
		void Render(HDC hdc) override;


		virtual void Enter();
		virtual void Exit();

	private:
		PlayerProjectile* mPlayerAttack[WEAPON_POOL];
	};
}
