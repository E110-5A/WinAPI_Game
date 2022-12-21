#include "jsBarUI.h"

// resource
#include "jsImage.h"

//
#include "jsCreature.h"

namespace js
{
	BarUI::BarUI(eUIType type)
		: HUD(type)
	{
	}
	BarUI::~BarUI()
	{
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

		// 채력바 예시
		int max = mMaxValue;
		int cur = mCurValue;

		float xRatio = (mCurValue / mMaxValue);

		

		AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
			, mImage->GetWidth() * xRatio, mImage->GetHeight()
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
	}
	void BarUI::OnClear()
	{
	}
}