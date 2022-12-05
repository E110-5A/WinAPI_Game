#pragma once
#include "jsGameObject.h"

namespace js
{
	struct MonsterStat
	{
		float maxHp;		// 310
		float curHp;
		float def;			// 0
		float moveSpeed;	// 16
		float att;			// 13
	};

	enum class eMonsterState
	{
		Idle,
		Move,
		Skill,
		Death,
	};

	class Image;
	class PlayerProjectile;
	class Monster : public GameObject
	{
	public:
		Monster();
		Monster(Pos pos);
		virtual ~Monster();

		virtual void Initialize();

		virtual void InitStat() {};
		virtual void InitCollider() {};
		virtual void InitAnimator() {};
		virtual void InitRigidbody() {};

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		


		
		void SetImage(Image* image) { mImage = image; }
		Image* GetImage() { return mImage; }


		// ���ݼ��� �Լ�
		void SetMaxHp(float value) { mStat.maxHp = value; }
		float GetMaxHp() { return mStat.maxHp; }
		void SetCurHp(float value) { mStat.curHp = value; }
		float GetCurHp() { return mStat.curHp; }

		void SetMoveSpeed(float value) { mStat.moveSpeed = value; }
		float GetMoveSpeed() { return mStat.moveSpeed; }
		
		void SetDef(float value) { mStat.def = value; }
		float SetDef() { return mStat.def; }
		void SetAtt(float value) { mStat.att = value; }
		float GetAtt() { return mStat.att; }

		// None
		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;

		// ���
		void Hit(GameObject* attaker);
		void SelfDamaged(GameObject* attaker);
		// �Է¹��� �������� �з���
		void SelfKnockBack(GameObject* attaker);
		// �Է¹��� �� ���� �������� ����
		void SelfStrun();

	protected:
		Collider*	mCollider;
		Rigidbody*	mRigidbody;
		Animator*	mAnimator;

	private:
		Image*			mImage;
		MonsterStat		mStat;
	};
}

