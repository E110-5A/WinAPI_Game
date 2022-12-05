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
		virtual void InitStat() override;
		virtual void InitCollider() override;
		virtual void InitAnimator() override;
		virtual void InitRigidbody() override;

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

// hp�� 0�Ʒ��� destroy

		// �÷��̾��� ��� ret

		// ����ü�� ��� -hp

		// �������� ��� ���� ����

