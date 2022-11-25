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
		float AttSpeed;		// 정확한 수치 ㅁ?ㄹ
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
			Idle,		// 아무 상태로 변환 가능
			Move,		// 아무 상태로 변환 가능
			Jump,		// 아무 상태로 변환 가능
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

		// 애니메이션 재생 로직
		void PlayAnim();

		
		// 애니메이션 이벤트
		void ReturnIdle();


		void SetHp(int hp) { mHp = hp; }
		int GetHp() { return mHp; }



		// 충돌관련 설정
	public:
		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;
		

		// 상태
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

		// 컴포넌트
	private:
		Animator*	mAnimator;
		Collider*	mCollider;
		Rigidbody*	mRigidbody;


	private:
		Image*		mImage;
		Vector2		mDir;
		eState		mState;
		PlayerStat	mStat;

		// 임시
	private:
		float	mSpeed;
		int		mHp;
	};
}

