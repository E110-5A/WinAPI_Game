#include "jsBossHpBar.h"

#include "jsImage.h"
#include "jsBossMonster.h"
namespace js
{
	BossHpBar::BossHpBar(eUIType type)
		: HUD(type)
		, mTarget(nullptr)
		, mHealth(nullptr)
	{
	}
	BossHpBar::~BossHpBar()
	{
	}

	void BossHpBar::OnInit()
	{
	}
	void BossHpBar::OnActive()
	{
	}
	void BossHpBar::OnInActive()
	{
	}
	void BossHpBar::OnTick()
	{
	}
	void BossHpBar::OnRender(HDC hdc)
	{
		if (nullptr == mImage)
			return;

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;
		
		mMax = mHealth->maxHP;
		mCur = mHealth->curHP;
		
		float temp = (mMax / 100);

		float xRatio = (mCur / temp) / 100;

		AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
			, mImage->GetWidth() * xRatio, mImage->GetHeight()
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
	}
	void BossHpBar::OnClear()
	{
	}
	void BossHpBar::SetTarget(BossMonster* target)
	{
		mTarget = target; 
		mHealth = mTarget->GetHealth();
	}
}