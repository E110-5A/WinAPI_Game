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
		, mIsLoop (true)
	{
	}

	Animator::~Animator()
	{
		for (auto iter : mAnimations)
		{
			delete iter.second;
		}
		for (auto iter : mEvents)
		{
			delete iter.second;
		}
	}

	void Animator::Tick()
	{
		if (nullptr != mCurAnimation)
		{
			mCurAnimation->Tick();

			if (mIsLoop && mCurAnimation->isComplete())
			{
				Animator::Events* events = FindEvents(mCurAnimation->GetName());
				if (nullptr != events)
					events->mCompleteEvent();
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
		// 애니메이션 중복검사
		Animation* animation = FindAnimation(name);
		if (nullptr != animation)
		{
			MessageBox(nullptr, L"중복 키 애니메이션 생성", L"애니메이션 생성 실패", MB_OK);
			return;
		}

		// 애니메이션에서 새로 만듦
		animation = new Animation();		
		animation->Create(image, leftTop, size, offset, 
			spriteLength, duration, bAffectedCamera);
		animation->SetName(name);
		animation->SetAnimator(this);
		mAnimations.insert(std::make_pair(name, animation));
		
		Events* events = new Events();
		mEvents.insert(std::make_pair(name, events));
	}

	void Animator::CreateAnimation(const std::wstring& path, const std::wstring& name, Vector2 offset, float duration)
	{
		UINT width = 0;
		UINT height = 0;
		UINT fileCount = 0;
		std::filesystem::path fs(path.c_str());

		std::vector<Image*> images;

		for (auto& p : std::filesystem::recursive_directory_iterator(path))
		{
			std::wstring fileName = p.path().filename();
			

			std::wstring keyString = CreateAniamtionKey(path);
			

			std::wstring fullName = path + L"\\" + fileName;

			Image* image = Resources::Load<Image>(keyString, fullName);
			images.push_back(image);

			if (width < image->GetWidth())
				width = image->GetWidth();
			if (height < image->GetHeight())
				height = image->GetHeight();
			++fileCount;
		}

		mSpriteSheet = Image::Create(name, width * fileCount, height);
		int idx = 0;
		for (Image* image : images)
		{
			BitBlt(mSpriteSheet->GetDC(), width * idx, 0, image->GetWidth(), image->GetHeight(), image->GetDC(), 0, 0, SRCCOPY);
			++idx;
		}

		CreateAnimation(name, mSpriteSheet, Vector2(0.f, 0.f), Size(width, height), offset, fileCount, duration);
	}

	void Animator::Play(const std::wstring& name, bool bLoop)
	{
		Animator::Events* events = FindEvents(name);
		if (nullptr != events)
			events->mStartEvent();
		Animation* prevAnimation = mCurAnimation;
		mCurAnimation = FindAnimation(name);
		mCurAnimation->Reset();
		mIsLoop = bLoop;

		// 이전과 다른 애니메이션이 나오면 EndEvent
		if (prevAnimation != mCurAnimation)
		{
			if (nullptr != events)
				events->mEndEvent();
		}
	}

	std::wstring Animator::CreateAniamtionKey(std::wstring path)
	{
		std::wstring keyString = path;
		// 애니메이션 폴더 이름 추출
		auto pos = keyString.find_last_of(L"\\");
		std::wstring tail = keyString.substr(pos + 1, keyString.length());
		keyString = keyString.substr(0, pos);

		// 애니메이션 오브젝트 이름 추출
		pos = keyString.find_last_of(L"\\");
		std::wstring head = keyString.substr(pos + 1, keyString.length());
		keyString = head + tail;

		return keyString;
	}





	Animator::Events* Animator::FindEvents(const std::wstring& key)
	{
		std::map<std::wstring, Events*>::iterator iter = mEvents.find(key);
		if (iter == mEvents.end())
		{
			return nullptr;
		}
		return iter->second;
	}
	std::function<void()>& Animator::GetStartEvents(const std::wstring& key)
	{
		Events* events = FindEvents(key);

		return events->mStartEvent.mEvent;
	}
	std::function<void()>& Animator::GetCompleteEvents(const std::wstring& key)
	{
		Events* events = FindEvents(key);

		return events->mCompleteEvent.mEvent;
	}
	std::function<void()>& Animator::GetEndEvents(const std::wstring& key)
	{
		Events* events = FindEvents(key);

		return events->mEndEvent.mEvent;
	}
}