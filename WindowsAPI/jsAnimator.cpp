#include "jsAnimator.h"
#include "jsGameObject.h"
#include "jsCamera.h"
#include "jsImage.h"
#include "jsResources.h"
#include "jsAnimation.h"

namespace js
{
	Animator::Animator()
		: Component(eComponentType::Animator)
		, mCurAnimation(nullptr)
		, mImage(nullptr)
		, mIsLoop (true)
	{
		//mImage = Resources::Load<Image>(L"Player", L"..\\Resources\\Image\\Player\\idle.bmp");
	}

	Animator::~Animator()
	{

	}

	void Animator::Tick()
	{
		if (nullptr != mCurAnimation)
		{
			mCurAnimation->Tick();

			if (mIsLoop && mCurAnimation->isComplete())
			{
				mCompleteEvent();
				mCurAnimation->Reset();
			}
		}
	}

	void Animator::Render(HDC hdc)
	{
		if (nullptr != mCurAnimation)
			mCurAnimation->Render(hdc);

	}
	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		std::map<std::wstring, Animation*>::iterator iter = mAnimations.find(name);
		if (iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}
	void Animator::CreateAnimation(const std::wstring& name, 
		Image* image, Vector2 leftTop, Size size, Vector2 offset, UINT spriteLength, float duration, bool bAffectedCamera)
	{
		// �ִϸ��̼� �ߺ��˻�
		Animation* animation = FindAnimation(name);
		if (nullptr != animation)
		{
			MessageBox(nullptr, L"�ߺ� Ű �ִϸ��̼� ����", L"�ִϸ��̼� ���� ����", MB_OK);
			return;
		}

		// �ִϸ��̼ǿ��� ���� ����
		animation = new Animation();		
		animation->Create(image, leftTop, size, offset, 
			spriteLength, duration, bAffectedCamera);

		animation->SetName(name);
		animation->SetAnimator(this);


		mAnimations.insert(std::make_pair(name, animation));
	}
	void Animator::Play(const std::wstring& name, bool bLoop)
	{
		mStartEvent();
		Animation* prevAnimation = mCurAnimation;
		mCurAnimation = FindAnimation(name);
		mCurAnimation->Reset();
		mIsLoop = bLoop;

		// ������ �ٸ� �ִϸ��̼��� ������ EndEvent
		if (prevAnimation != mCurAnimation)
		{
			mEndEvent();
		}
	}
}