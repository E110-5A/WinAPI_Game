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

		void SetSkillInfo(SkillInfo* skill) { mSkillInfo = skill; }

	private:
		SkillInfo* mSkillInfo;
	};
}