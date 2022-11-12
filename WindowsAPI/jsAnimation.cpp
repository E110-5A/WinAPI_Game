#include "jsAnimation.h"
#include "jsImage.h"
#include "jsAnimator.h"
#include "jsGameObject.h"
#include "jsCamera.h"
#include "jsTime.h"

namespace js
{
	Animation::Animation()
	{
	}
	Animation::~Animation()
	{
	}
	void Animation::Tick()
	{
		if (mIsComplate)
			return;

		mTime += Time::GetDeltaTime();

		// �������ӵ��� �����ϴ� �ð��� �ѱ���
		if (mSpriteSheet[mSpriteIndex].duration < mTime)
		{
			mTime = 0.f;

			if (mSpriteSheet.size() <= mSpriteIndex + 1)
				mIsComplate = true;
			else
				++mSpriteIndex;
		}
	}
	void Animation::Render(HDC hdc)
	{
		// ���� ������ �����ͼ� ������ ��ǥ ì���
		GameObject* gameObj = mAnimator->GetOwner();
		Pos pos = gameObj->GetPos();
		Size scale = gameObj->GetScale();

		if (mAffectedCamera)
			pos = Camera::CalculatePos(pos);

		BLENDFUNCTION func = {};
		func.AlphaFormat = AC_SRC_ALPHA;
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.SourceConstantAlpha = 255;

		pos += mSpriteSheet[mSpriteIndex].offset;

		AlphaBlend(hdc,
			int(pos.x - mSpriteSheet[mSpriteIndex].size.x / 2.f), 
			int(pos.y - mSpriteSheet[mSpriteIndex].size.y / 2.f),
			int(mSpriteSheet[mSpriteIndex].size.x * scale.x),
			int(mSpriteSheet[mSpriteIndex].size.y * scale.y),
			mImage->GetDC(), 
			int(mSpriteSheet[mSpriteIndex].leftTop.x),
			int(mSpriteSheet[mSpriteIndex].leftTop.y),
			int(mSpriteSheet[mSpriteIndex].size.x),
			int(mSpriteSheet[mSpriteIndex].size.y), func);
	}

	void Animation::Create(Image* image, Vector2 leftTop, Size size, Vector2 offset, 
		UINT spriteLength, float duration, bool bAffectedCamera)
	{// �ִϸ����ͷκ��� ������ ������
		mImage = image;
		mAffectedCamera = bAffectedCamera;

		// ��������Ʈ ����
		for (size_t i = 0; i < spriteLength; i++)
		{
			Sprite sprite;
			sprite.leftTop.x = leftTop.x + (size.x * (float)i);
			sprite.leftTop.y = leftTop.y;
			sprite.size = size;
			sprite.offset = offset;
			sprite.duration = duration;

			mSpriteSheet.push_back(sprite);
		}
	}
	
	void Animation::Reset()
	{
		mSpriteIndex = 0;
		mTime = 0.f;
		mIsComplate = false;
	}
}