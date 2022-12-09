#include "jsCamera.h"
#include "jsApplication.h"
#include "jsGameObject.h"
#include "jsInput.h"
#include "jsTime.h"
#include "jsImage.h"

namespace js
{
	Size Camera::mResoultion = Vector2::Zero;
	Pos Camera::mLookPosition = Vector2::Zero;
	Vector2 Camera::mDistance = Vector2::Zero;
	GameObject* Camera::mTarget = nullptr;

	eCameraEffect Camera::mEffect = eCameraEffect::None;
	Image* Camera::mBlind = nullptr;
	float Camera::mAlphaTime = 0.f;
	float Camera::mBlindAlpha = 0.f;
	float Camera::mEndTime = 2.f;

	void Camera::Initialize()
	{
		WindowData data = Application::GetInstance().GetWindowData();

		mResoultion = Vector2(data.width, data.height);
		// 해상도의 중심 위치가 현재 카메라의 위치
		mLookPosition = (mResoultion / 2.f);
		//mEffect = eCameraEffect::FadeIn;
		mBlind = Image::Create(L"Blind", data.width, data.height);
	}


	void Camera::Tick()
	{
		// 카메라 효과 기능
		if (mEffect != eCameraEffect::None)
		{
			if (mAlphaTime <= mEndTime)
			{
				mAlphaTime += Time::GetDeltaTime();

				// 현재 시간에서 종료 시간까지 비율 구하기
				float ratio = (mAlphaTime / mEndTime);

				if (eCameraEffect::FadeIn == mEffect)
				{
					mBlindAlpha = 1.f - ratio;
				}
				else if (eCameraEffect::FadeOut == mEffect)
				{
					mBlindAlpha = ratio;
				}
			}
		}

		// 타겟이 있으면 추격카메라
		if (nullptr != mTarget)
			mLookPosition = mTarget->GetPos();

		// 월드와 로컬간의 간격차를 계산
		mDistance = mLookPosition - (mResoultion / 2.f);
		// 현재 카메라 위치에서 해상도 절반 값을 뺀 길이
	}
	void Camera::Render(HDC hdc)
	{
		wchar_t szFloat[40] = {};

		std::wstring stateStr = L"Camera Posision :";
		stateStr += L" (";
		stateStr += std::to_wstring((int)mLookPosition.x);
		stateStr += L" , ";
		stateStr += std::to_wstring((int)mLookPosition.y);
		stateStr += L")";

		swprintf_s(szFloat, 40, stateStr.c_str());
		int strLen = wcsnlen_s(szFloat, 40);
		TextOut(hdc, 10, 40, szFloat, strLen);
		// 투명도가 0에 가까워지면 렌더링하지 않음
		if (mBlindAlpha <= 0.f)
			return;

		BLENDFUNCTION func = {};
		func.AlphaFormat = 0;
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.SourceConstantAlpha = (BYTE)(255.f * mBlindAlpha);

		AlphaBlend(hdc,
			0, 0, mBlind->GetWidth(), mBlind->GetHeight(),
			mBlind->GetDC(), 
			0, 0, mBlind->GetWidth(), mBlind->GetHeight(), func);

	}
	void Camera::CameraMove()
	{
		if (KEY_PRESSE(eKeyCode::W))
		{
			mLookPosition.y += -200 * Time::GetDeltaTime();
		}
		if (KEY_PRESSE(eKeyCode::S))
		{
			mLookPosition.y += 200 * Time::GetDeltaTime();
		}
		if (KEY_PRESSE(eKeyCode::A))
		{
			mLookPosition.x += -200 * Time::GetDeltaTime();
		}
		if (KEY_PRESSE(eKeyCode::D))
		{
			mLookPosition.x += 200 * Time::GetDeltaTime();
		}
	}
}