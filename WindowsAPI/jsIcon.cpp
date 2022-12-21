#include "jsIcon.h"

// resource
#include "jsImage.h"

//
#include "jsCreature.h"

namespace js
{
	Icon::Icon(eUIType type)
		: HUD(type)
		, mMaxValue(1.f)
		, mCurValue(1.f)
	{
	}
	Icon::~Icon()
	{
	}

	void Icon::OnInit()
	{
	}
	void Icon::OnActive()
	{
	}
	void Icon::OnInActive()
	{
	}
	void Icon::OnTick()
	{
	}
	void Icon::OnRender(HDC hdc)
	{
		if (nullptr == mImage)
			return;

		float max = mMaxValue;
		float cur = mMaxValue - mCurValue;

		float ratio = (cur / max);

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255 * ratio;

		AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
			, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
	}
	void Icon::OnClear()
	{
	}
}