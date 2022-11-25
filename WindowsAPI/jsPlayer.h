#pragma once
#include "jsGameObject.h"

namespace js
{
	struct PlayerStat
	{
		float MaxHp;		// 110				+ 32
		float CurHp;
		float RegenHp;		// 0.6				+ 0.12
		float Def;			// 0				+ 2
		float MoveSpeed;	// 1.3
		float Att;			// 12				+ 3
		float AttSpeed;		// ��Ȯ�� ��ġ ��?��
		float AttRange;		// 700
	};

	class Image;
	class Animator;
	class Collider;
	class Rigidbody;
	class Player :
		public GameObject
	{
	public:
		enum class eState
		{
			Idle,		// �ƹ� ���·� ��ȯ ����
			Move,		// �ƹ� ���·� ��ȯ ����
			Jump,		// �ƹ� ���·� ��ȯ ����
			Climb,		
			Attack,		
			Dodge,		
			Die,		
		};

		Player();
		Player(Pos pos);
		~Player();

		void Init();
		void InitAnim();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		// �ִϸ��̼� ��� ����
		void PlayAnim();

		
		// �ִϸ��̼� �̺�Ʈ
		void ReturnIdle();


		void SetHp(int hp) { mHp = hp; }
		int GetHp() { return mHp; }



		// �浹���� ����
	public:
		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;
		

		// ����
	public:
		void SetState(eState state) { mState = state; }
		eState GetState() { return mState; }

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
		Image*		mImage;
		Vector2		mDir;
		eState		mState;
		PlayerStat	mStat;

		// �ӽ�
	private:
		float	mSpeed;
		int		mHp;
	};
}

