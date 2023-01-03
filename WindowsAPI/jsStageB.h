#pragma once
#include "jsScene.h"

namespace js
{
	class StageB : public Scene
	{
	public:
		StageB();
		~StageB();

		void Initialize() override;

		void InitBG();

		void Tick() override;
		void Render(HDC hdc) override;

		virtual void Enter() override;		// 해당 씬으로 변경될 때 호출
		virtual void Exit() override;

		void EnterLayer();
		void EnterObject();
		void EnterUI();
	private:
		Chest* mChest[CHEST_POOL];
		Teleporter* mTeleporter;
	};
}
