#pragma once
#include "jsMonster.h"

namespace js
{
	class Component;
	class Animator;
	class Rigidbody;
	class Imp : public Monster
	{
	public:
		Imp();
		Imp(Pos pos);
		~Imp();

		virtual void Initialize()override;
		virtual void SetComponent() override;
		void SetAnimator();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		// None
		virtual void OnCollisionEnter(Collider* other);
		virtual void OnCollisionStay(Collider* other);
		virtual void OnCollisionExit(Collider* other);

	private:
		eMonsterState	mState;
	};
}

// hp가 0아래면 destroy

		// 플레이어인 경우 ret

		// 투사체인 경우 -hp

		// 점프대인 경우 위로 점프

