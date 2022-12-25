#pragma once
#include "jsHUD.h"

namespace js
{
	class DifficultyHUD : public HUD
	{
	public:
		DifficultyHUD(eUIType type);
		virtual ~DifficultyHUD();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnTick() override;
		virtual void OnRender(HDC hdc) override;
		virtual void OnClear() override;

	};
}