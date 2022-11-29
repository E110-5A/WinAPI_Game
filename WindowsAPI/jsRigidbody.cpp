#include "jsRigidbody.h"
#include "jsTime.h"
#include "jsGameObject.h"

namespace js
{
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mMass(1.0f)
		, mForce(Vector2::Zero)
		, mVelocity(Vector2::Zero)
		, mAccelation(Vector2::Zero)
		, mFriction(150.f)
	{
		mGravity = Vector2(0.0f, 800.0f);
		mIsGround = true;
		mLimitVelocity = Vector2(1000.0f, 1400.0f);
	}
	Rigidbody::~Rigidbody()
	{
	}
	void Rigidbody::Tick()
	{
		// �⺻ ���� (F = M * A)		
		// ���ӵ� ���ϱ� (A = F / M)
		mAccelation = mForce / mMass;
		// �ӵ� ���ϱ� (A * T * Default)
		mVelocity += (mAccelation * Time::GetDeltaTime()) * 300.0f;

		// �߷� ����
		GravityAction();
		// ������ ����
		FrictionAction();
		// �ӵ� ����
		LimitVelocityAction();

		// �̵���Ű��
		Pos pos = GetOwner()->GetPos();
		pos += mVelocity * Time::GetDeltaTime();
		GetOwner()->SetPos(pos);
		mForce.Clear();
	}
	void Rigidbody::Render(HDC hdc)
	{
		wchar_t szFloat[40] = {};
		
		Pos pos = GetOwner()->GetPos();
		std::wstring postr = std::to_wstring(pos.x);
		postr += L":" + std::to_wstring(pos.y);

		swprintf_s(szFloat, 40, postr.c_str());
		int strLen = wcsnlen_s(szFloat, 40);
		TextOut(hdc, 10, 50, szFloat, strLen);
	}

	void Rigidbody::GravityAction()
	{
		// �߷� ����
		if (mIsGround)
		{
			Vector2 gravity = mGravity;
			gravity.Normalize();
			float dot = math::Dot(mVelocity, gravity);
			mVelocity -= gravity * dot;
		}
		else
		{
			mVelocity += mGravity * Time::GetDeltaTime() * 2.0f;
		}
	}

	void Rigidbody::FrictionAction()
	{
		if (!(mVelocity == Vector2::Zero))
		{
			// �ӵ��� �ݴ� ����
			Vector2 friction = -mVelocity;
			friction = friction.Normalize() * mFriction * mMass * Time::GetDeltaTime();

			// �������� ���� �ڵ�
			if (mForce == Vector2::Zero)
				friction += friction * 3;



			// �������� �ӵ��� �ѱ��
			if (friction.Length() > mVelocity.Length())
			{
				mVelocity = Vector2::Zero;
			}
			else
			{
				mVelocity += friction;
			}
		}
	}
	void Rigidbody::LimitVelocityAction()
	{
		// �ӵ� ���� �и� (����, ����)
		Vector2 gravity = mGravity;
		gravity.Normalize();
		float dot = math::Dot(mVelocity, gravity);
		gravity *= dot;
		Vector2 sideVelocity = mVelocity - gravity;

		// ���� �ӵ� ����
		if (gravity.Length() > mLimitVelocity.y)
		{
			gravity.Normalize();
			gravity *= mLimitVelocity.y;
		}
		// ���� �ӵ� ����
		if (sideVelocity.Length() > mLimitVelocity.x)
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitVelocity.x;
		}
		mVelocity = gravity + sideVelocity;
	}
}