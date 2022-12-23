#pragma once
#include "jsCreature.h"

#define PLAYER_SIZE_X 25
#define PLAYER_SIZE_Y 34

namespace js
{	
	struct SkillInfo
	{
		float		damage;				// 피해량 비율
		eStagger	stagger;			// 관통 단계
		float		power;				// 위력 (피해와 연관없음)

		float		castDelay;			// 스킬 지연시간
		float		castDelayTime;		
		float		coolDown;			// 스킬 재사용 대기시간
		float		coolDownTime;

		int			maxCount;			// 반복 횟수
		int			curCount;

		bool		active;				// 사용불가 상태		: 쿨다운 대기
		bool		run;				// 진행중 상태		: 스킬 내부로직 조건용
		bool		finish;				// 끝난 상태			: 상태 종료 조건
	};

	class Image;
	class Animator;
	class Collider;
	class Rigidbody;
	class GameObject;
	class PlayerProjectile;
	class GroundCheck;
	class Player : public Creature
	{
	public:
		Player();
		Player(Pos pos);
		~Player();

		void InitAnim();
		void InitSkill(SkillInfo& skill, float damage, float power, int maxCount, float castDelay, float coolDown, eStagger	stagger = eStagger::Light);

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		virtual void InitComponent() override;
		virtual void AddComponentScene() override;

		// 애니메이션
		//void ReturnIdle();
		
		// 씬에서 반드시 투사체와 연결할 것
		void SetWeapon(PlayerProjectile* weapon)
		{
			// 투사체 객체 개수 제한
			if (PLAYER_PROJECTILE_POOL == mWeaponID)
				return;

			// 투사체 연동
			mWeapon[mWeaponID] == nullptr;
			mWeapon[mWeaponID] = weapon;
			++mWeaponID;
		}

		//
		void SetBlocking(bool isBlock) { mBlocking = isBlock; }
		bool GetBlocking() { return mBlocking; }

	public:
		// 스스로 함수 호출
		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;
		

	public:
		// 상태
		void SetState(ePlayerState state) { mState = state; }
		ePlayerState GetState() { return mState; }


		//
		SkillInfo& GetDubleTabInfo() { return mDubleTab; }
		SkillInfo& GetFMJInfo() { return mFMJ; }
		SkillInfo& GetTacticalDiveInfo() { return mTacticalDive; }
		SkillInfo& GetSupressiveFireInfo() { return mSupressiveFire; }

	private:
		void Idle();
		void Move();
		void Jump();
		void Climb();
		void DoubleTab();
		void FMJ();
		void TacticalDive();
		void SupressiveFire();
		void Death();

	private:
		// 기능
		void Cooldown();
		void SkillProcess();
		void Skill(eProjectileType type);
		void JumpProcess();

	private:
		ePlayerState		mState;

		PlayerProjectile*	mWeapon[PLAYER_PROJECTILE_POOL];
		int					mWeaponID;

		SkillInfo			mDubleTab;
		SkillInfo			mFMJ;
		SkillInfo			mSupressiveFire;
		SkillInfo			mTacticalDive;

		// 외부요인
	private:
		bool				mBlocking;
	};
}
