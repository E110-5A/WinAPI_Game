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
			child->mIsEnable = true;
			child->OnActive();
		}
	}

	void UIBase::InActive()
	{
		mIsEnable = false;
		for (UIBase* child : mChilds)
		{
			child->OnInActive();
			child->mIsEnable = false;
		}
		OnInActive();
		mIsEnable = false;
	}

	void UIBase::Tick()
	{
		if (false == mIsEnable)
			return;
		OnTick();

		if (mParent)
			mScreenPos = mParent->GetPos() + mPos;
		else
			mScreenPos = mPos;

		for (UIBase* child : mChilds)
		{
			if (child->mIsEnable)
				child->Tick();
		}
	}

	void UIBase::Render(HDC hdc)
	{
		if (false == mIsEnable)
			return;
		OnRender(hdc);
		for (UIBase* child : mChilds)
		{
			if (child->mIsEnable)
				child->OnRender(hdc);
		}
	}

	void UIBase::UIClear()
	{
		for (UIBase* child : mChilds)
		{
			if (child->mIsEnable)
				child->OnClear();
		}
		OnClear();
	}
	void UIBase::ImageLoad(const std::wstring& key, const std::wstring& path)
	{
		mImage = Resources::Load<Image>(key, path);
		SetSize(Vector2(mImage->GetWidth(), mImage->GetHeight()));
	}

	void UIBase::AddChild(UIBase* uiBase)
	{
		mChilds.push_back(uiBase);
		uiBase->mParent = this;
	}
}