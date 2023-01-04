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


		// ���̵��� 5�� �����Ҷ����� Lenth�� 1 ������
		float maxLenth = 45;		
		float temp = (maxLenth / 100);
		float yLenth = (float)*mDifficulty;
		
		// ���� ���̵��� �ִ볭�̵����� ���ۼ�Ʈ���� �� (��������)
		float ratio = (yLenth / temp) / 100;

		// max -> 0
		float LTratio = 1 - ratio;


		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;

		AlphaBlend(hdc
			// �׷��� �̹��� �������� (max���� ������������ y���� ���ؾ���)
			, (int)mScreenPos.x, (int)mScreenPos.y + mImage->GetHeight() * LTratio
			// �����ϴ� �̹��� ũ�� (0���� ������������ y ���� ���ؾ���)
			, mImage->GetWidth(), mImage->GetHeight() * ratio
			// ���� �̹��� �������� (max���� ������������ y ���� ���ؾ���)
			, mImage->GetDC(), 0, mImage->GetHeight() * ratio,
			// ���� �̹��� ũ��
			mImage->GetWidth(), mImage->GetHeight() * LTratio, func);
	}

	void DifficultyHUD::OnClear()
	{
	}
}