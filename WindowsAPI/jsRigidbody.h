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

		void AddForce(Vector2 force) { mForce += force; }
		void SetMass(float mass) { mMass = mass; }
		void SetGround(bool isGround) { mIsGround = isGround; }
		bool IsGrounded() { return mIsGround; }
		Vector2 GetVelocity() { return mVelocity; }
		void SetVelocity(Vector2 velocity) { mVelocity = velocity; }


	private:
		void GravityAction();
		void FrictionAction();
		void LimitVelocityAction();

	private:
		float	mMass;		// 질량
		float	mFriction;	// 마찰력
		Vector2 mForce;		// 가해지는 힘
		Vector2 mVelocity;	// 속도
		Vector2 mAccelation;// 가속도

		Vector2 mGravity;
		bool	mIsGround;
		Vector2	mLimitVelocity;	// 최대 제한속도

	};
}