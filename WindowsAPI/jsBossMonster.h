#pragma once
#include "jsCreature.h"

namespace js
{
	enum class eBossType
	{
		Colossus,
		End,
	};
	enum class eBossState
	{
		Stay,
		Chase,
		Attack1,
		Attack2,
		Death,
	};

	class Player;
	class MonsterAttack;
	class BossMonster : public Creature
	{
	public:
		BossMonster();
		BossMonster(Pos pos);
		virtual ~BossMonster();

		virtual void Initialize();

		void SetAnimator();

		// 충돌체, 스텟
		void InitColossus();

		void InitSkill(MonsterSkillInfo* skill, float damage, float castDelay, float coolDown);

		// 텔레포터에 의해서 스폰됨(?)
		void Spawn();


		// 부모 함수 호출
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;


		// 상태
		void Stay();
		void Chase();
		void Attack1();
		void Attack2();
		void Death();

		void Cooldown();
		void SkillProcess();
		void Skill(eBossAttackType type);
		void DeadCheck();

		void AddBoss();

		// None
		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		// 충돌 기능
		virtual void SelfHit(GameObject* attaker, float damage, eStagger stagger, float power) override;
		virtual void SelfDamaged(float damage) override;

	private:
		eBossType			mBossType;
		int					mEyesight;

		eBossState			mState;
		Player*				mTarget;

		MonsterSkillInfo*	mAttack1;
		MonsterSkillInfo*	mAttack2;

		MonsterAttack*		mDamageObj;


	private:
		int					mDropExp;
	};
}