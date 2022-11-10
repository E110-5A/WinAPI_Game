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
	class Player :
		public GameObject
	{
	public:
		Player();
		Player(Pos pos);
		~Player();

		void Init();
		void InitAnim();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void PlayAnim();

		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;

		void WalkComplete();
		void ActionComplete();

	private:
		float mSpeed;
		Image* mImage;

		Animator* mAnimator;
		Collider* mCollider;

		PlayerStat mStat;

	};
}

