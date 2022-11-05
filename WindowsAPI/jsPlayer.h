#pragma once
#include "jsGameObject.h"

namespace js
{
	class Image;
	class Animator;

	class Player :
		public GameObject
	{
	public:
		Player();
		Player(Pos pos);
		~Player();

		void Init();
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;

		void WalkComplete();

	private:
		float mSpeed;
		Image* mImage;

		Animator* mAnimator;
	};
}

