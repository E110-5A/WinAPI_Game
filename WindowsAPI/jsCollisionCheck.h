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

		// 바닥에 충돌했을때 ground 설정
		virtual void Process(Collider* other);

	protected:
		Creature* mOwner;
		Collider* mCollider;
	};	
}