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

		// W A S D Ű�� ī�޶� ��ġ ����
		static void CameraMove();

	private:
		Camera() = default;
		~Camera() = default;
		
	private:
		static Size mResoultion;	// �ػ�
		static Pos mLookPosition;	// ī�޶� ��ġ
		static Vector2 mDistance;	// �ػ� �߽���ǥ�� ī�޶� ��ġ���� ����
		static GameObject* mTarget; // ī�޶� �߰� ���


		static eCameraEffect mEffect;
		static Image* mBlind;
		static float mAlphaTime;
		static float mBlindAlpha;
		static float mEndTime;
	};
}