#pragma once
#include "jsGameObject.h"

namespace js
{
	struct PlayerStat
	{
		float maxHp;		// 110				+ 32
		float curHp;
		float regenHp;		// 0.6				+ 0.12
		float def;			// 0				+ 2
		float moveSpeed;	// 1.3
		float att;			// 12				+ 3
		float attSpeed;		// 정확한 수치 ㅁ?ㄹ
		float range;		// 700
	};

	class Image;
	class Animator;
	class Collider;
	class Rigidbody;
	class PlayerProjectile;
	class Player : public GameObject
	{
	public:
		Player();
		Player(Pos pos);
		~Player();

		void Init();
		void InitStat();
		void InitAnim();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		// 애니메이션
		void PlayAnim();				
		void ReturnIdle();

		
		// 변수
		PlayerStat GetInfo() { return mStat; }
		void SetWeapon(PlayerProjectile* weapon) { mWeapon = weapon; }
		void SetHp(int hp) { mHp = hp; }
		int GetHp() { return mHp; }
		void SetSpeed(float value) { mSpeed = value; }



	public:
		// 충돌관련 설정
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
		void Attack();
		void Dodge();
		void Die();

		// 컴포넌트
	private:
		Animator*	mAnimator;
		Collider*	mCollider;
		Rigidbody*	mRigidbody;


	private:
		Image*				mImage;
		ePlayerState		mState;
		PlayerStat			mStat;
		PlayerProjectile*	mWeapon;

		// 임시
	private:
		float	mSpeed;
		int		mHp;
	};
}

