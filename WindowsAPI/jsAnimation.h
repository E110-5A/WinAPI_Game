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
			Vector2 leftTop;	// 시작좌표
			Size	size;		// 스프라이트 가로세로 크기
			Vector2 offset;		
			float	duration;	// 프레임 유지시간

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

