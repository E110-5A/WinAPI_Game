#pragma once
#include "jsScene.h"

namespace js
{
	class StageA : public Scene
	{
	public:
		StageA();
		~StageA();

		void Initialize() override;

		void InitBG();

		void Tick() override;
		void Render(HDC hdc) override;

		virtual void Enter() override;		// �ش� ������ ����� �� ȣ��
		virtual void Exit() override;

		void EnterLayer();
		void EnterObject();
		void EnterUI();

	private:
		Chest* mChest[CHEST_POOL];
		Teleporter* mTeleporter;
	};
}
