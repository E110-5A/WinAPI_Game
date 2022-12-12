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
	class PlayerProjectile;
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

		


		
		void SetImage(Image* image) { mImage = image; }
		Image* GetImage() { return mImage; }


		// ���ݼ��� �Լ�
		void InitHealth(float hp, float regen, float defance, float moveSpeed)
		{
			mMonsterHealth.maxHP = hp;
			mMonsterHealth.curHP = hp;
			mMonsterHealth.healthRegen = regen;
			mMonsterHealth.defance = defance;
			mMonsterHealth.moveSpeed = moveSpeed;
		}

		void InitOffence(float damage, float attackSpeed, float range)
		{
			mMonsterOffence.damage = damage;
			mMonsterOffence.attackSpeed = attackSpeed;
			mMonsterOffence.criticalChance = 0;
			mMonsterOffence.range = range;
		}

		// None
		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		// ���
		void SelfHit(GameObject* attaker, float damage, eStagger stagger, float power);
		void SelfDamaged(float damage);
		// �Է¹��� �������� �з���
		void SelfKnockBack(float dir, eStagger stagger, float power);
		// �Է¹��� �� ���� �������� ����
		void SelfStun(float power);

	protected:
		Collider*	mCollider;
		Rigidbody*	mRigidbody;
		Animator*	mAnimator;

	private:
		Image*			mImage;
		Health			mMonsterHealth;
		Offence			mMonsterOffence;
		eStagger		mMonsterResistance;
	};
}

