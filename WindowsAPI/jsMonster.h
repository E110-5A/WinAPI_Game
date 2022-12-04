#pragma once
#include "jsGameObject.h"

namespace js
{
	struct MonsterStat
	{
		float maxHp;		// 310
		float curHp;
		float def;			// 0
		float moveSpeed;	// 16
		float att;			// 13
	};

	enum class eMonsterState
	{
		Idle,
		Move,
		Skill,
		Death,
	};

	class Image;
	class Monster : public GameObject
	{
	public:
		Monster();
		Monster(Pos pos);
		virtual ~Monster();

		virtual void Initialize();

		virtual void InitStat() {};
		virtual void InitCollider() {};
		virtual void InitAnimator() {};
		virtual void InitRigidbody() {};

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		// ���
		// �Է¹��� �� ��ŭ HP ����
		void Damaged();
		// �Է¹��� �������� �з���
		void KnockBack();
		// �Է¹��� �� ���� �������� ����
		void Strun();


		// �浹����
		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		// ���ط� �Է�
		void Hit(float value) {};

	private:
		Image* mImage;
	};
}

