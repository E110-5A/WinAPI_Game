#pragma once
#include "jsHUD.h"

namespace js
{
	class Icon : public HUD
	{
	public:
		Icon(eUIType type);
		~Icon();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

		void SetMaxValue(float& maxValue) { mMaxValue = maxValue; }
		void SetCurValue(float& curValue) { mCurValue = curValue; }

	private:
		float		mMaxValue;
		float		mCurValue;
	};
}