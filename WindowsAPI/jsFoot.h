#pragma once
#include "jsCollisionCheck.h"

namespace js
{
	class Collider;
	class Creature;
	class Foot : public CollisionCheck
	{
	public:
		Foot();
		~Foot();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;

		// Climb���¿��� Foot�� Platform�� �浹�Ұ��

		void ClimbDown(Collider* other);
		void PlatformCollision(Collider* other);

	};
}