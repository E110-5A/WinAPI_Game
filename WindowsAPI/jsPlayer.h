#pragma once
#include "jsGameObject.h"

namespace js
{
	struct PlayerStat
	{
		float maxHp;		// 110				+ 32
		float curHp;
		float regenHp;		// 0.6				+ 0.12
		float def;			// 0				+ 2
		float moveSpeed;	// 1.3
		float att;			// 12				+ 3
		float attSpeed;		// ��Ȯ�� ��ġ ��?��
		float range;		// 700
	};

	struct SkillInfo
	{
		float damage;
		float castDelay;
		int hitCount;
		float coolDown;
		bool unable;
		float deletaTime;
	};

	class Image;
	class Animator;
	class Collider;
	class Rigidbody;
	class PlayerProjectile;

	class Player : public GameObject
	{
	public:
		Player();
		Player(Pos pos);
		~Player();

		void Init();
		void InitStat();
		void InitAnim();
		void InitSkill();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		// �ִϸ��̼�
		void PlayAnim();				
		void ReturnIdle();

		
		// ����
		PlayerStat GetInfo() { return mStat; }
		void SetWeapon(PlayerProjectile* weapon) 
		{
			if (6 == mWeaponID)
				return;
			mWeapon[mWeaponID] == nullptr;
			mWeapon[mWeaponID] = weapon;
			mWeaponID++;
		}
		void SetHp(int hp) { mHp = hp; }
		int GetHp() { return mHp; }
		void SetSpeed(float value) { mSpeed = value; }

		// ���
		void Cooldown();
		void Attack(ePlayerAttackType type);	

	public:
		// �浹���� ����
		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;
		

	public:
		// ����
		void SetState(ePlayerState state) { mState = state; }
		ePlayerState GetState() { return mState; }

		void Idle();
		void Move();
		void Jump();
		void Climb();
		void Attack();
		void Dodge();
		void Die();

		// ������Ʈ
	private:
		Animator*	mAnimator;
		Collider*	mCollider;
		Rigidbody*	mRigidbody;


	private:
		Image*				mImage;
		PlayerStat			mStat;
		ePlayerState		mState;



	private:
		PlayerProjectile*	mWeapon[WEAPON_POOL];
		int					mWeaponID;

		SkillInfo			mDubleTab;
		SkillInfo			mFMJ;
		SkillInfo			mSupressiveFire;
		SkillInfo			mTacticalDive;

		// �ӽ�
	private:
		float	mSpeed;
		int		mHp;
		float				mDelayTime;
		int					mFireCount;
	};
}
