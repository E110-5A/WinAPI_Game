#pragma once
#include "jsGameObject.h"

namespace js
{
	class Collider;
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

		void SetOwner(GameObject* owner) { mOwner = owner; }
		GameObject* GetOwner() { return mOwner; }

	private:
		GameObject* mOwner;
		Collider*	mCollider;
	};
}