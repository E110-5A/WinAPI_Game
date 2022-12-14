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


		// 스텟설정 함수
		void InitMonsterStat(float hp, float regen, float defance, float damage, float attackSpeed, float range, float moveSpeed)
		{
			mMonsterHealth.maxHP = hp;
			mMonsterHealth.curHP = hp;
			mMonsterHealth.healthRegen = regen;
			mMonsterHealth.defance = defance;
			
			mMonsterOffence.damage = damage;
			mMonsterOffence.attackSpeed = attackSpeed;
			mMonsterOffence.criticalChance = 0;
			mMonsterOffence.range = range;

			mMonsterUtility.moveSpeed = moveSpeed;
			mMonsterUtility.maxJumpCount = 1;
			mMonsterUtility.curJumpCount = 0;
		}


		// None
		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		// 기능
		void SelfHit(GameObject* attaker, float damage, eStagger stagger, float power);
		void SelfDamaged(float damage);
		// 입력받은 방향으로 밀려남
		void SelfKnockBack(float dir, eStagger stagger, float power);


		// FSM 만들때 추후 추가할 예정
		void SelfStun(float power);

	protected:
		Collider*	mCollider;
		Rigidbody*	mRigidbody;
		Animator*	mAnimator;

	private:
		Image*			mImage;
		Health			mMonsterHealth;
		Offence			mMonsterOffence;
		Utility			mMonsterUtility;
		eStagger		mMonsterResistance;
	};
}

