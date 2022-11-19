#include "jsButton.h"
#include "jsImage.h"
#include "jsInput.h"

namespace js
{
	Button::Button(eUIType type)
		: UIBase(type)
	{
		mOnClick = std::bind(&Button::Click, this);
	}
	Button::~Button()
	{
	}
	void Button::OnInit()
	{
	}
	void Button::OnActive()
	{
		UIBase::OnActive();
	}
	void Button::OnInActive()
	{
		UIBase::OnInActive();
	}
	void Button::OnTick()
	{
		Pos mousePos = Input::GetMousePos();
		Size size = GetSize();

		if (mScreenPos.x <= mousePos.x && mousePos.x < mScreenPos.x + size.x
			&& mScreenPos.y <= mousePos.y && mousePos.y < mScreenPos.y + size.y)
			mIsMouseOn = true;
		else
			mIsMouseOn = false;


		if (KEY_DOWN(eKeyCode::LBTN) && mIsMouseOn)
			mOnClick();
	}

	void Button::OnRender(HDC hdc)
	{
		BLENDFUNCTION func = {};
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.AlphaFormat = AC_SRC_ALPHA;
		func.SourceConstantAlpha = 255;

		AlphaBlend(hdc, (int)mScreenPos.x, (int)mScreenPos.y
			, mImage->GetWidth(), mImage->GetHeight()
			, mImage->GetDC(), 0, 0, mImage->GetWidth(), mImage->GetHeight(), func);
	}
	void Button::OnClear()
	{
	}
	void Button::Click()
	{
		int a = 0;
	}
}