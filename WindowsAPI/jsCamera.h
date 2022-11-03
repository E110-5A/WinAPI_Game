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

		static void SetTarget(GameObject* target) { mTarget = target; }
		static Pos CalculatePos(Pos pos) { return pos - mDistance; }
		void SetCameraEffect(eCameraEffect effect) { mEffect = effect; }



	private:
		Camera() = default;
		~Camera() = default;
		
	private:
		static Size mResoultion;
		static Pos mLookPosition;
		static Vector2 mDistance;
		static GameObject* mTarget;


		static eCameraEffect mEffect;
		static Image* mBlind;
		static float mAlphaTime;
		static float mBlindAlpha;
		static float mEndTime;
	};
}