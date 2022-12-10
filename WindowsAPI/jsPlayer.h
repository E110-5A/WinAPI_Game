#pragma once
#include "jsGameObject.h"

namespace js
{
	
	struct SkillInfo
	{
		float	damage;
		float	castDelay;			// 스킬 지연시간
		float	castDelayTime;
		int		maxCount;					// 반복 횟수
		int		curCount;
		float	coolDown;				// 스킬 재사용 대기시간
		float	coolDownTime;
		bool	unable;				// 사용불가 상태		: 쿨다운 대기
		bool	on;					// 진행중 상태		: 스킬 내부로직 조건용
		bool	finish;				// 끝난 상태			: 상태 종료 조건
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

		// 애니메이션
		//void ReturnIdle();
		
		// 변수
		//PlayerStat GetInfo() { return mStat; }
		void SetWeapon(PlayerProjectile* weapon) 
		{
			if (WEAPON_POOL == mWeaponID)
				return;

			mWeapon[mWeaponID] == nullptr;
			mWeapon[mWeaponID] = weapon;
			++mWeaponID;
		}

		// 기능
		void Cooldown();
		void SkillProcess();
		void Skill(eProjectileType type);
		void SelfDamaged(Monster* other);

	public:
		// 스스로 함수 호출
		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;
		
	public:
		// 상태
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

		// 컴포넌트
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
