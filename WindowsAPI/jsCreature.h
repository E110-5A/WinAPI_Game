#pragma once
#include "jsGameObject.h"
#include "jsRigidbody.h"

namespace js
{
	class Image;
	class Animator;
	class Rigidbody;
	class Foot;
	class Head;
	class Creature : public GameObject
	{
	public:
		Creature();
		Creature(Pos pos);
		virtual ~Creature();

		// 상속 함수
		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;
		
		// 초기화
		virtual void InitComponent();
		virtual void AddComponentScene();
		void SetStat(Health* health, Offence* offence, Utility* utility)
		{
			mHealthStat = health;
			mOffenceStat = offence;
			mUtilityStat = utility;
		}
		void SetMonsterStat(float hp, float regen, float defance, float damage, float attackSpeed, float range, float moveSpeed)
		{
			mHealthStat = new Health;
			mHealthStat->maxHP = hp;
			mHealthStat->curHP = hp;
			mHealthStat->healthRegen = regen;
			mHealthStat->defance = defance;

			mOffenceStat = new Offence;
			mOffenceStat->damage = damage;
			mOffenceStat->attackSpeed = attackSpeed;
			mOffenceStat->criticalChance = 0;
			mOffenceStat->range = range;

			mUtilityStat = new Utility;
			mUtilityStat->moveSpeed = moveSpeed;
			mUtilityStat->maxJumpCount = 1;
			mUtilityStat->curJumpCount = 0;
		}

		// 기능
		void BodyCollision(GameObject* other);
		void SetGround(bool isGround) { mRigidbody->SetGround(isGround); }
		void JumpCountReset() { mUtilityStat->curJumpCount = 0; }

		// 가해자 오브젝트, 맞은 피해량, 스테거, 위력
		virtual void SelfHit(GameObject* attaker, float damage, eStagger stagger, float power = 40);
		virtual void SelfDamaged(float damage);
		virtual void SelfKnockBack(float dir, eStagger stagger, float power = 40);
		virtual void SelfStun(float power = 40);



		// GetSet
		void SetImage(Image* image) { mSpriteImage = image; }
		Image* GetImage() { return mSpriteImage; }

		Health* GetHealth() { return mHealthStat; }
		Offence* GetOffence() { return mOffenceStat; }
		Utility* GetUtility() { return mUtilityStat; }

		Animator* GetAnimator() { return mAnimator; }
		Rigidbody* GetRigidbody() { return mRigidbody; }


	protected:
		Animator*		mAnimator;
		Rigidbody*		mRigidbody;
		Collider*		mHeadCollider;
		Collider*		mBodyCollider;
		Collider*		mFootCollider;

	protected:
		Health*			mHealthStat;
		Offence*		mOffenceStat;
		Utility*		mUtilityStat;
		eStagger		mResistance;

	protected:
		Foot*			mFootObject;
		Head*			mHeadObject;
		Image*			mSpriteImage;
	};
}