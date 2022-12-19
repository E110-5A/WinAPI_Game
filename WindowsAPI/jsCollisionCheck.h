#pragma once
#include "jsGameObject.h"

namespace js
{
	class Creature;
	class Collider;
	class CollisionCheck : public GameObject
	{
	public:
		CollisionCheck();
		virtual ~CollisionCheck();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;

		void SetOwner(Creature* owner) { mOwner = owner; }
		Creature* GetOwner() { return mOwner; }

		// �ٴڿ� �浹������ ground ����
		virtual void Process(Collider* other);

	protected:
		Creature* mOwner;
		Collider* mCollider;
	};	
}