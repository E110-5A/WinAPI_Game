#pragma once
#include "jsEntity.h"

namespace js
{
	class Animator;
	class Image;
	class Animation : public Entity
	{
	public:
		struct Sprite
		{
			Vector2 leftTop;	// ������ǥ
			Size	size;		// ��������Ʈ ���μ��� ũ��
			Vector2 offset;		
			float	duration;	// ������ �����ð�

			Sprite()
				: leftTop(0.f, 0.f)
				, size(0.f, 0.f)
				, offset(0.f, 0.f)
				, duration(0.f)
			{}
		};

		Animation();
		~Animation();

		void Tick();
		void Render(HDC hdc);
		void Create(Image* image, Vector2 leftTop, Size size, Vector2 offset,
			UINT spriteLength, float duration, bool bAffectedCamera);

		void Reset();
		bool isComplete() { return mIsComplate; }
		void SetAnimator(Animator* animator) { mAnimator = animator; }

	private:
		Animator* mAnimator;
		Image* mImage;
		std::vector<Sprite> mSpriteSheet;
		UINT mSpriteIndex;
		float mTime;

		bool mStart;
		bool mIsComplate;
		bool mEnd;
		bool mAffectedCamera;
	};
}

