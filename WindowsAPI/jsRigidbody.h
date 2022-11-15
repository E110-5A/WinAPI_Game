#pragma once
#include "jsComponent.h"
namespace js
{
	class Rigidbody : public Component
	{
	public:
		Rigidbody();
		~Rigidbody();

		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		void AddForce(Vector2 force);
		void SetMass(float mass) { mMass = mass; }

	private:
		float	mMass;		// 질량
		float	mFriction;	// 마찰력
		Vector2 mForce;		// 가해지는 힘
		Vector2 mVelocity;	// 속도
		Vector2 mAccelation;// 가속도

		Vector2 mGravity;
		bool	mIsGround;
		Vector2	mLimitVelocity;	// 최대 중력 속도
	};
}