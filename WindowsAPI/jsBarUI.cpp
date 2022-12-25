#include "jsBarUI.h"

// resource
#include "jsImage.h"

//
#include "jsCreature.h"

namespace js
{
	BarUI::BarUI(eUIType type)
		: HUD(type)
		, mBarType(eBarType::HP)
		, mTarget(nullptr)
		, mHealth(nullptr)
		, mExp(nullptr)
	{
		mTarget = new Creature();
		mHealth = new Health();
		mExp = new PlayerInfo();
	}
	BarUI::~BarUI()
	{
		delete mTarget;
		delete mHealth;
		delete mExp;
	}

	void BarUI::OnInit()
	{
	}
	void BarUI::OnActive()
	{
	}
	void BarUI::OnInActive()
	{
	}
	void BarUI::OnTick()
	{
	}
	void BarUI::OnRender(HDC hdc)
	{
		if (nullptr == mImage)
			return;

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;


		if (eBarType::HP == mBarType)
		{
			mMax = mHealth->maxHP;
			mCur = mHealth->curHP;
		}
		else if (eBarType::EXP == mBarType)
		{
			mMax = mExp->maxExp;
			mCur = mExp->curExp;
		}

		float temp = (mMax / 100);

		float xRatio = (mCur / temp) / 100;

		AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
			, mImage->GetWidth() * xRatio, mImage->GetHeight()
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
	}
	void BarUI::OnClear()
	{
	}
}