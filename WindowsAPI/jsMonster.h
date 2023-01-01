#pragma once
#include "jsCreature.h"


#include "jsScene.h"
#include "jsSceneManager.h"



namespace js
{
	enum class eMonsterType
	{
		Imp,
		Parent,
		End,
	};

	enum class eMonsterState
	{
		Stay,
		Chase,
		Skill,
		Stun,
		Death,
	};

	class Image;
	class Platform;
	class Player;
	class MonsterAttack;
	class Monster : public Creature
	{
	public:
		Monster();
		Monster(Pos pos);
		virtual ~Monster();

		virtual void Initialize();

		void SetAnimator();
		void ReturnIdle();
		void DeathAnimation();

		// �浹ü, ����
		void InitImp();
		
		// �浹ü, ����
		void InitParent();
		void InitSkill(float damage, float castDelay, float coolDown);

		// ���ӸŴ����� ���ؼ� ������
		void Spawn(Platform* spawnPlatform);


		// �θ� �Լ� ȣ��
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;
		

		// ����
		void Stay();
		void Chase();
		void Attack();
		void Stun();
		void Death();

		void Cooldown();
		void SkillProcess();
		void Skill();
		void DeadCheck();

		void AddMonster();

		// None
		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		// �浹 ���
		virtual void SelfHit(GameObject* attaker, float damage, eStagger stagger, float power) override;
		virtual void SelfDamaged(float damage) override;
		virtual void SelfKnockBack(float dir, eStagger stagger, float power) override;
		// FSM ���鶧 ���� �߰��� ����
		void SelfStun(float power);

	private:
		eMonsterType	mMonsterType;
		int				mEyesight;

		eMonsterState	mState;
		Player*			mTarget;


		MonsterSkillInfo*	mSkillInfo;
		MonsterAttack*		mDamageObj;


	private:
		int				mDropExp;
	};
}

