#pragma once
#include "jsComponent.h"

namespace js 
{
	class Animation;
	class Image;
	class Animator : public Component
	{
	public:

		// 콜백같은 기능 (델리게이트?)
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				// 함수는 r-value(코드영역)이기 때문에 move를 통해서 옮겨줘야함
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}

			std::function<void()> mEvent;
		};

		Animator();
		~Animator();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		Animation* FindAnimation(const std::wstring& name);
		void CreateAnimation(const std::wstring& name, 
			Image* image, Vector2 leftTop, Size size, Vector2 offset,
			UINT spriteLength, float duration, bool bAffectedCamera = true);

		void Play(const std::wstring& name, bool bLoop = true);


	public:
		Event								mStartEvent;
		Event								mCompleteEvent;
		Event								mEndEvent;

	private:
		Image*								mImage;

	private:

		std::map<std::wstring, Animation*>	mAnimations;
		Animation*							mCurAnimation;
		bool								mIsLoop;
	};
}

