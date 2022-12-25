#include "jsDifficultyHUD.h"

// resource
#include "jsImage.h"

namespace js
{
	DifficultyHUD::DifficultyHUD(eUIType type)
		: HUD(type)
	{
	}
	DifficultyHUD::~DifficultyHUD()
	{
	}
	void DifficultyHUD::OnInit()
	{
	}
	void DifficultyHUD::OnActive()
	{
	}
	void DifficultyHUD::OnInActive()
	{
	}
	void DifficultyHUD::OnTick()
	{
	}
	void DifficultyHUD::OnRender(HDC hdc)
	{
		if (nullptr == mImage)
			return;

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;

		AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
			, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetDC(), 0, 0,
			mImage->GetWidth(), mImage->GetHeight(), func);
	}

	void HUD::OnClear()
	{
	}
}