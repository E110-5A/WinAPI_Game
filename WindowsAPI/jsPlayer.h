#pragma once
#include "jsGameObject.h"

namespace js
{
	
	struct SkillInfo
	{
		float	damage;				// ���ط� ����
		float	power;				// ���� (���ؿ� ��������)
		float	castDelay;			// ��ų �����ð�
		float	castDelayTime;		
		int		maxCount;			// �ݺ� Ƚ��
		int		curCount;
		float	coolDown;			// ��ų ���� ���ð�
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
		void InitSkill(SkillInfo& skill, float damage, float power, int maxCount, float castDelay, float coolDown);

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		// �ִϸ��̼�
		//void ReturnIdle();
		
		// ������ �ݵ�� ����ü�� ������ ��
		void SetWeapon(PlayerProjectile* weapon)
		{
			// ����ü ��ü ���� ����
			if (PLAYER_PROJECTILE_POOL == mWeaponID)
				return;

			// ����ü ����
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
		ePlayerState		mState;
		Health				mHealth;
		Offence				mOffence;
		Utility				mUtility;

	private:
		PlayerProjectile*	mWeapon[PLAYER_PROJECTILE_POOL];
		int					mWeaponID;

		SkillInfo			mDubleTab;
		SkillInfo			mFMJ;
		SkillInfo			mSupressiveFire;
		SkillInfo			mTacticalDive;
	};
}
