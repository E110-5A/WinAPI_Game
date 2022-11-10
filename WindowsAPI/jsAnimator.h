#pragma once
#include "jsComponent.h"

namespace js 
{
	class Animation;
	class Image;
	class Animator : public Component
	{
	public:

		// �ݹ鰰�� ��� (��������Ʈ?)
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				// �Լ��� r-value(�ڵ念��)�̱� ������ move�� ���ؼ� �Ű������
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}

			std::function<void()> mEvent;
		};

		// �� �ִϸ��̼Ǹ��� 3���� �̺�Ʈ�� ������
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

		// Ű���� ���� �ִϸ������� map�� ����� �ִϸ��̼��� ������
		Animation* FindAnimation(const std::wstring& name);

		// bmp���Ͽ� ��� ��������Ʈ�� �ִϸ��̼��� ����
		void CreateAnimation(const std::wstring& name, 
			Image* image, Vector2 leftTop, Size size, Vector2 offset,
			UINT spriteLength, float duration, bool bAffectedCamera = true);

		// ���͸��� ��� bmp ���ϵ�� �ִϸ��̼��� ����
		void CreateAnimation(const std::wstring& path, const std::wstring& name, Vector2 offset = Vector2::Zero, float duration = 0.1f);

		// Ű���� ���� map�� ����� �ִϸ��̼��� �ҷ���, �⺻�� loop
		void Play(const std::wstring& name, bool bLoop = true);


	public:
		// Ű���� ���� map Event�� ����� �̺�Ʈ�� �ҷ���
		Events* FindEvents(const std::wstring& key);

		std::function<void()>& GetStartEvents(const std::wstring& key);
		std::function<void()>& GetCompleteEvents(const std::wstring& key);
		std::function<void()>& GetEndEvents(const std::wstring& key);




	private:
		std::map<std::wstring, Animation*>	mAnimations;

		// �ִϸ��̼��� �̸��� Ű������ �� �ִϸ��̼Ǹ��� 3���� �̺�Ʈ�� ����
		std::map<std::wstring, Events*>		mEvents;

		Animation*							mCurAnimation;
		bool								mIsLoop;

		Image*								mSpriteSheet;
	};
}

