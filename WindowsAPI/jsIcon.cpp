#include "jsIcon.h"

// resource
#include "jsImage.h"

//
#include "jsCreature.h"

namespace js
{
	Icon::Icon(eUIType type)
		: HUD(type)
		, mSkillInfo(nullptr)
	{
		mSkillInfo = new SkillInfo();
	}
	Icon::~Icon()
	{
		mSkillInfo->~SkillInfo();
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

		
		float max = mSkillInfo->coolDown;
				
		float cur = mSkillInfo->coolDownTime;
		
		float ratio = (cur / max);




		if (0 == mSkillInfo->coolDownTime || mSkillInfo->coolDownTime >= mSkillInfo->coolDown)
			ratio = 1;

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