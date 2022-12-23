#pragma once
#include "jsGameObject.h"

namespace js
{

	class DamageObject : public GameObject
	{
	public:
		DamageObject();
		DamageObject(Pos pos);
		~DamageObject();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC _hdc) override;

		// 타격 대상의 함수 호출
		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;

		// 외부에서 호출됨
		Offence GetOffence() { return mOffence; }
	private:
		Collider*	mCollider;
		Offence		mOffence;
	};
}