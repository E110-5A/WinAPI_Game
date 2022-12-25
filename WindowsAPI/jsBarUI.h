#pragma once
#include "jsHUD.h"

namespace js
{
	enum class eBarType
	{
		HP,
		EXP,
	};

	class Creature;
	class BarUI : public HUD
	{
	public:
		BarUI(eUIType type);
		~BarUI();

		void SetType(eBarType type) { mBarType = type; }



		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;



		void SetHealth(Health* hp) { mHealth = hp; }
		void SetExp(PlayerInfo* exp) { mExp = exp; }

	private:
		eBarType	mBarType;
		Creature*	mTarget;

		Health*		mHealth;
		PlayerInfo*	mExp;

		float mMax;
		float mCur;
	};
}