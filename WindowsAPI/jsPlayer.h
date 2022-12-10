#pragma once
#include "jsGameObject.h"

namespace js
{
	
	struct SkillInfo
	{
		float	damage;
		float	castDelay;			// ��ų �����ð�
		float	castDelayTime;
		int		maxCount;					// �ݺ� Ƚ��
		int		curCount;
		float	coolDown;				// ��ų ���� ���ð�
		float	coolDownTime;
		bool	unable;				// ���Ұ� ����		: ��ٿ� ���
		bool	on;					// ������ ����		: ��ų ���η��� ���ǿ�
		bool	finish;				// ���� ����			: ���� ���� ����
	};

	class Image;
	class Animator;
	class Collider;
	class Rigidbody;
	class PlayerProjectile;
	class Monster;

	class Player : public GameObject
	{
	public:
		Player();
		Player(Pos pos);
		~Player();

		void SetComponent();
		void InitAnim();
		void InitSkill();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		// �ִϸ��̼�
		//void ReturnIdle();
		
		// ����
		//PlayerStat GetInfo() { return mStat; }
		void SetWeapon(PlayerProjectile* weapon) 
		{
			if (WEAPON_POOL == mWeaponID)
				return;

			mWeapon[mWeaponID] == nullptr;
			mWeapon[mWeaponID] = weapon;
			++mWeaponID;
		}

		// ���
		void Cooldown();
		void SkillProcess();
		void Skill(eProjectileType type);
		void SelfDamaged(Monster* other);

	public:
		// ������ �Լ� ȣ��
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
		void DoubleTab();
		void FMJ();
		void TacticalDive();
		void SupressiveFire();
		void Death();

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
	};
}
