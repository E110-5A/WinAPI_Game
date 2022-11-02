#pragma once
#include "Common.h"

namespace js
{
	class GameObject;
	class Camera
	{
	public:
		static void Initialize();
		static void Tick();

		static void SetTarget(GameObject* target) { mTarget = target; }

		static Pos CalculatePos(Pos pos) { return pos - mDistance; }




	private:
		Camera() = default;
		~Camera() = default;
		
	private:
		static Size mResoultion;
		static Pos mLookPosition;
		static Vector2 mDistance;
		static GameObject* mTarget;
	};
}