#pragma once
#include "jsScene.h"

namespace js
{
	class Chest;
	class TestScene2 : public Scene
	{
	public:
		TestScene2();
		~TestScene2();

		void Initialize() override;

		void TileLoadTest();
		void InitBG();
		void InitObject();
		void SetLayer();
		void SetUI();

		void Tick() override;
		void Render(HDC hdc) override;


		virtual void Enter();
		virtual void Exit();

	private:
		Chest* mChest[CHEST_POOL];
	};
}
