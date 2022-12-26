#pragma once
#include "jsScene.h"

namespace js
{
	class Chest;
	class TestScene : public Scene
	{
	public:
		TestScene();
		~TestScene();

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
		Chest*				mChest[CHEST_POOL];
	};
}
