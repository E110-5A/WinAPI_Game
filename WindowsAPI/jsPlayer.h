#pragma once
#include "jsCreature.h"

#define PLAYER_SIZE_X 25
#define PLAYER_SIZE_Y 34

namespace js
{	
	struct SkillInfo
	{
		float		damage;				// ���ط� ����
		eStagger	stagger;			// ���� �ܰ�
		float		power;				// ���� (���ؿ� ��������)

		float		castDelay;			// ��ų �����ð�
		float		castDelayTime;		
		float		coolDown;			// ��ų ���� ���ð�
		float		coolDownTime;

		int			maxCount;			// �ݺ� Ƚ��
		int			curCount;

		bool		active;				// ���Ұ� ����		: ��ٿ� ���
		bool		run;				// ������ ����		: ��ų ���η��� ���ǿ�
		bool		finish;				// ���� ����			: ���� ���� ����
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

		//
		void SetBlocking(bool isBlock) { mBlocking = isBlock; }
		bool GetBlocking() { return mBlocking; }

	public:
		// ������ �Լ� ȣ��
		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;
		

	public:
		// ����
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
		// ���
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

		// �ܺο���
	private:
		bool				mBlocking;
	};
}
