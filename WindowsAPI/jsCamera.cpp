#include "jsCamera.h"
#include "jsApplication.h"
#include "jsGameObject.h"
#include "jsInput.h"
#include "jsTime.h"

namespace js
{
	Size Camera::mResoultion = Vector2::Zero;
	Pos Camera::mLookPosition = Vector2::Zero;
	Vector2 Camera::mDistance = Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;

	void Camera::Initialize()
	{
		WindowData data = Application::GetInstance().GetWindowData();

		mResoultion = Vector2(data.width, data.height);
		mLookPosition = (mResoultion / 2.f);
	}
	void Camera::Tick()
	{
		if (nullptr != mTarget)
			mLookPosition = mTarget->GetPos();

		mDistance = mLookPosition - (mResoultion / 2.f);
	}
}