#pragma once
#include "Common.h"

namespace js
{
	class Image;
	class GameObject;
	class Camera
	{
	public:
		static void Initialize();
		static void Tick();
		static void Render(HDC hdc);

		static Pos CalculateObjectPos(Pos pos) { return pos - mDistance; }
		static Pos CalculateMousePos(Pos pos) { return pos + mDistance; }
		static void SetTarget(GameObject* target) { mTarget = target; }
		static void SetCameraEffect(eCameraEffect effect) { mEffect = effect; }

		// W A S D 키로 카메라 위치 변경
		static void CameraMove();

	private:
		Camera() = default;
		~Camera() = default;
		
	private:
		static Size mResoultion;	// 해상도
		static Pos mLookPosition;	// 카메라 위치
		static Vector2 mDistance;	// 해상도 중심좌표와 카메라 위치간의 간격
		static GameObject* mTarget; // 카메라 추격 대상


		static eCameraEffect mEffect;
		static Image* mBlind;
		static float mAlphaTime;
		static float mBlindAlpha;
		static float mEndTime;
	};
}