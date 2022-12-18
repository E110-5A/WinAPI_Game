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
		mIsGround = false;
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
	}

	void Rigidbody::GravityAction()
	{
		// 중력 제거
		if (mIsGround)
		{
			VelocityControl(mGravity, mVelocity);
		}
		// 중력 적용
		else
		{
			// 현재 속도를 중력의 영향에 받도록 한다 (현재 속도의 y성분에 중력 가속도에 비례한 값을 추가한다)
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
				mVelocity = Vector2::Zero;
			else
				mVelocity += friction;
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

		// 수직 속도 제한 적용
		if (gravity.Length() > mLimitVelocity.y)
		{
			gravity.Normalize();
			gravity *= mLimitVelocity.y;
		}
		// 수평 속도 제한 적용
		if (sideVelocity.Length() > mLimitVelocity.x)
		{
			sideVelocity.Normalize();
			sideVelocity *= mLimitVelocity.x;
		}

		// 수평속도 수직속도를 합친다
		mVelocity = gravity + sideVelocity;
	}

	void Rigidbody::VelocityControl(Vector2 dir, Vector2 velocity)
	{
		// 단위벡터 구하기
		Vector2 unit = dir;
		unit.Normalize();

		// 현재 속도의 y성분 추출 (속도와 중력의 단위벡터 내적 : 중력의 단위벡터와 내적하기 때문에 속도의 y성분만 추출된다)
		float dot = math::Dot(unit, velocity);

		// 추출한 벡터의 성분을 역방향으로 더해서 속도값을 0으로 만든다
		mVelocity -= unit * dot;
	}
}