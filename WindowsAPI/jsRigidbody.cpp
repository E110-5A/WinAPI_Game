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
		// 기본 공식 (F = M * A)		
		// 가속도 구하기 (A = F / M)
		mAccelation = mForce / mMass;
		// 속도 구하기 (A * T * Default)
		mVelocity += (mAccelation * Time::GetDeltaTime()) * 300.0f;

		// 중력 적용
		GravityAction();
		// 마찰력 적용
		FrictionAction();
		// 속도 제한
		LimitVelocityAction();

		// 이동시키기
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
		// 중력 적용
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
			// 속도에 반대 방향
			Vector2 friction = -mVelocity;
			friction = friction.Normalize() * mFriction * mMass * Time::GetDeltaTime();

			// 급제동을 위한 코드
			if (mForce == Vector2::Zero)
				friction += friction * 3;



			// 마찰력이 속도를 넘기면
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
		// 속도 성분 분리 (수직, 수평)
		Vector2 gravity = mGravity;
		gravity.Normalize();
		float dot = math::Dot(mVelocity, gravity);
		gravity *= dot;
		Vector2 sideVelocity = mVelocity - gravity;

		// 수직 속도 제한
		if (gravity.Length() > mLimitVelocity.y)
		{
			gravity.Normalize();
			gravity *= mLimitVelocity.y;
		}
		// 수평 속도 제한
		if (sideVelocity.Length() > mLimitVelocity.x)
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitVelocity.x;
		}
		mVelocity = gravity + sideVelocity;
	}
}