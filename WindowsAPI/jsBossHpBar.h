#pragma once
#include "jsHUD.h"




namespace js
{
	class BossMonster;
	class BossHpBar : public HUD
	{
	public:
		BossHpBar(eUIType type);
		~BossHpBar();


		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;


		void SetHealth(Health* hp) { mHealth = hp; }
		void SetTarget(BossMonster* target);

	private:
		BossMonster*	mTarget;

		Health*			mHealth;

		float			mMax;
		float			mCur;
	};
}