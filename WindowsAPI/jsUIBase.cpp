#include "jsUIBase.h"
#include "jsResources.h"
#include "jsImage.h"

namespace js
{
	UIBase::UIBase(eUIType type)
		: mType(type)
		, mIsFullScreen(false)
		, mIsEnable(false)
		, mParent(nullptr)
		, mPos(Vector2::Zero)
		, mSize(Vector2::Zero)
	{
	}

	UIBase::~UIBase()
	{
	}

	void UIBase::Initialize()
	{
		OnInit();

		for (UIBase* child : mChilds)
		{
			child->OnInit();
		}
	}

	void UIBase::Active()
	{
		mIsEnable = true;
		OnActive();
		for (UIBase* child : mChilds)
		{
			child->OnActive();
		}
	}

	void UIBase::InActive()
	{
		mIsEnable = false;
		for (UIBase* child : mChilds)
		{
			child->OnInActive();
		}
		OnInActive();
	}

	void UIBase::Tick()
	{
		if (false == mIsEnable)
			return;
		OnTick();

		if (mParent)
			mScreenPos = (mParent->GetScreenPos() + mPos);
		else
			mScreenPos = (mPos);

		for (UIBase* child : mChilds)
		{
			if (child->mIsEnable)
				child->OnTick();
		}
	}

	void UIBase::Render(HDC hdc)
	{
		if (false == mIsEnable)
			return;
		OnRender(hdc);

	}

	void UIBase::UIClear()
	{
		OnClear();
	}
	void UIBase::ImageLoad(const std::wstring& key, const std::wstring& path)
	{
		mImage = Resources::Load<Image>(key, path);
		SetSize(Vector2(mImage->GetWidth(), mImage->GetHeight()));
	}
}