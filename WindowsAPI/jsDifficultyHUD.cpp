#include "jsDifficultyHUD.h"

// resource
#include "jsImage.h"

namespace js
{
	DifficultyHUD::DifficultyHUD(eUIType type)
		: HUD(type)
		, mDifficulty(nullptr)
	{
		mDifficulty = new int;
		*mDifficulty = 0;
	}
	DifficultyHUD::~DifficultyHUD()
	{
		delete mDifficulty;
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


		// 난이도가 5씩 증가할때마다 Lenth가 1 증가함
		float maxLenth = 45;		
		float temp = (maxLenth / 100);
		float yLenth = (float)*mDifficulty;
		
		// 현재 난이도가 최대난이도에서 몇퍼센트인지 값 (오름차순)
		float ratio = (yLenth / temp) / 100;

		// max -> 0
		float LTratio = 1 - ratio;


		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;

		AlphaBlend(hdc
			// 그려질 이미지 시작지점 (max부터 내림차순으로 y값이 변해야함)
			, (int)mScreenPos.x, (int)mScreenPos.y + mImage->GetHeight() * LTratio
			// 복사하는 이미지 크기 (0부터 오름차순으로 y 값이 변해야함)
			, mImage->GetWidth(), mImage->GetHeight() * ratio
			// 원본 이미지 시작지점 (max부터 내림차순으로 y 값이 변해야함)
			, mImage->GetDC(), 0, mImage->GetHeight() * ratio,
			// 원본 이미지 크기
			mImage->GetWidth(), mImage->GetHeight() * LTratio, func);
	}

	void DifficultyHUD::OnClear()
	{
	}
}