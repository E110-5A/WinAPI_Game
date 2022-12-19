#pragma once
#include "jsGameObject.h"
#include "jsPlayerManager.h"

namespace js
{
	class Image;
	class Animator;
	class Rigidbody;
	class GroundCheck;
	class Creature : public GameObject
	{
	public:
		Creature();
		Creature(Pos pos);
		virtual ~Creature();

		// ��� �Լ�
		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;
		
		// �ʱ�ȭ
		virtual void SetComponent() override;

		void SetPlayerHealth(Health stat) { mHealthStat = stat; }
		void SetPlayerOffence(Offence stat) { mOffenceStat = stat; }
		void SetPlayerUtility(Utility stat) { mUtilityStat = stat; }

		void SetMonsterStat(float hp, float regen, float defance, float damage, float attackSpeed, float range, float moveSpeed)
		{
			mHealthStat.maxHP = hp;
			mHealthStat.curHP = hp;
			mHealthStat.healthRegen = regen;
			mHealthStat.defance = defance;

			mOffenceStat.damage = damage;
			mOffenceStat.attackSpeed = attackSpeed;
			mOffenceStat.criticalChance = 0;
			mOffenceStat.range = range;

			mUtilityStat.moveSpeed = moveSpeed;
			mUtilityStat.maxJumpCount = 1;
			mUtilityStat.curJumpCount = 0;
		}


		// GetSet
		void SetImage(Image* image) { mSpriteImage = image; }
		Image* GetImage() { return mSpriteImage; }

		Health& GetHealth() { return mHealthStat; }
		Offence& GetOffence() { return mOffenceStat; }
		Utility& GetUtility() { return mUtilityStat; }

		// ������ ������Ʈ, ���� ���ط�, ���װ�, ����
		virtual void SelfHit(GameObject* attaker, float damage, eStagger stagger, float power = 40);
		virtual void SelfDamaged(float damage);
		virtual void SelfKnockBack(float dir, eStagger stagger, float power = 40);
		virtual void SelfStun(float power = 40);

	protected:
		Animator*	mAnimator;
		Rigidbody*	mRigidbody;
		Collider*	mBodyCollider;
		Collider*	mFootCollider;

	protected:
		Health		mHealthStat;
		Offence		mOffenceStat;
		Utility		mUtilityStat;
		eStagger	mResistance;

	protected:
		GroundCheck*	mFootObject;
		Image*			mSpriteImage;
	};
}