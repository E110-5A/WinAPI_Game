#include "jsHUD.h"
#include "jsImage.h"
#include "jsPlayer.h"
namespace js
{
	HUD::HUD(eUIType type)
		: UIBase(type)
	{
	}
	HUD::~HUD()
	{
	}
	void HUD::OnInit()
	{
	}
	void HUD::OnActive()
	{
	}
	void HUD::OnInActive()
	{
	}
	void HUD::OnTick()
	{
	}
	void HUD::OnRender(HDC hdc)
	{
		if (nullptr == mImage)
			return;
		if (nullptr == mTarget)
			return;

		Player* playerObj = dynamic_cast<Player*>(mTarget);
		int hp = playerObj->GetHp();
		float xRatio = (hp / 100.0f);

		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;

		AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
			, mImage->GetWidth() * xRatio, mImage->GetHeight()
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
	}

	void HUD::OnClear()
	{
	}
}