#pragma once
#include "jsGameObject.h"

namespace js
{
	class Collider;
	class Creature;
	class CeilingCheck : public GameObject
	{
	public:
		CeilingCheck();
		~CeilingCheck();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;

		void SetOwner(Creature* owner) { mOwner = owner; }
		Creature* GetOwner() { return mOwner; }

		// 천장에 충돌했을때 ground 설정
		void CeilingProcess(Collider* other);

	private:
		Creature* mOwner;
		Collider* mCollider;
	};
}