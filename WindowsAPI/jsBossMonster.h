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

		// �浹ü, ����
		void InitColossus();

		void InitSkill(MonsterSkillInfo* skill, float damage, float castDelay, float coolDown);

		// �ڷ����Ϳ� ���ؼ� ������(?)
		void Spawn();


		// �θ� �Լ� ȣ��
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;


		// ����
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

		// �浹 ���
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