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

		// 각 애니메이션마다 3가지 이벤트를 소유함
		struct Events
		{
		public:
			Event		mStartEvent;
			Event		mCompleteEvent;
			Event		mEndEvent;
		};

		Animator();
		~Animator();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		// 키값을 통해 애니메이터의 map에 저장된 애니메이션을 가져옴
		Animation* FindAnimation(const std::wstring& name);

		// bmp파일에 담긴 스프라이트로 애니메이션을 만듦
		void CreateAnimation(const std::wstring& name, 
			Image* image, Vector2 leftTop, Size size, Vector2 offset,
			UINT spriteLength, float duration, bool bAffectedCamera = true);

		// 디렉터리에 담긴 bmp 파일들로 애니메이션을 만듦
		void CreateAnimation(const std::wstring& path, const std::wstring& name, Vector2 offset = Vector2::Zero, float duration = 0.1f);

		// 키값을 통해 map에 저장된 애니메이션을 불러옴, 기본값 loop
		void Play(const std::wstring& name, bool bLoop = true);


	public:
		// 키값을 통해 map Event에 저장된 이벤트를 불러옴
		Events* FindEvents(const std::wstring& key);

		std::function<void()>& GetStartEvents(const std::wstring& key);
		std::function<void()>& GetCompleteEvents(const std::wstring& key);
		std::function<void()>& GetEndEvents(const std::wstring& key);




	private:
		std::map<std::wstring, Animation*>	mAnimations;

		// 애니메이션의 이름을 키값으로 각 애니메이션마다 3가지 이벤트를 가짐
		std::map<std::wstring, Events*>		mEvents;

		Animation*							mCurAnimation;
		bool								mIsLoop;

		Image*								mSpriteSheet;
	};
}

