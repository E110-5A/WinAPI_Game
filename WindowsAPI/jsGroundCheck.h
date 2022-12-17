#pragma once
#include "jsGameObject.h"

namespace js
{
	class Collider;
	class Creature;
	class GroundCheck : public GameObject
	{
	public:
		GroundCheck();
		~GroundCheck();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;

		void SetOwner(Creature* owner) { mOwner = owner; }
		Creature* GetOwner() { return mOwner; }

		void SetGround(GameObject* other, bool isGround);

	private:
		Creature*	mOwner;
		Collider*	mCollider;
	};
}