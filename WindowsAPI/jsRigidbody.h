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
		float	mMass;		// ����
		float	mFriction;	// ������
		Vector2 mForce;		// �������� ��
		Vector2 mVelocity;	// �ӵ�
		Vector2 mAccelation;// ���ӵ�

		Vector2 mGravity;
		bool	mIsGround;
		Vector2	mLimitVelocity;	// �ִ� �߷� �ӵ�
	};
}