#pragma once
#include "jsGameObject.h"

namespace js
{
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
	};
}

