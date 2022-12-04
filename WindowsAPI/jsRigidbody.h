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
		float	mMass;		// ����
		float	mFriction;	// ������
		Vector2 mForce;		// �������� ��
		Vector2 mVelocity;	// �ӵ�
		Vector2 mAccelation;// ���ӵ�

		Vector2 mGravity;
		bool	mIsGround;
		Vector2	mLimitVelocity;	// �ִ� ���Ѽӵ�

	};
}