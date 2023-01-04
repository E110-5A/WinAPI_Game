#pragma once
#include "jsScene.h"
#include "jsUIManager.h"

namespace js
{
	class Chest;
	class Teleporter;
	class BossMonster;
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

		virtual void PushBossUI() override {
			UIManager::Push(eUIType::BossHp);
			BossHpBar* bossHpBar = UIManager::GetUIInstant<BossHpBar>(eUIType::BossHpBar);
			bossHpBar->SetTarget(mBossMonster);
		}
		virtual void PopBossUI() override { UIManager::Pop(eUIType::BossHpBar); }

		void Tick() override;
		void Render(HDC hdc) override;


		virtual void Enter();
		virtual void Exit();

	private:
		Chest*				mChest[CHEST_POOL];
		Teleporter*			mTeleporter;
		BossMonster*		mBossMonster;
	};
}
