#include "jsMonster.h"

// 매니저
#include "jsCamera.h"
// 리소스
#include "jsResources.h"
#include "jsImage.h"

// 컴포넌트
#include "jsCollider.h"
#include "jsAnimator.h"
#include "jsRigidbody.h"

// 오브젝트
#include "jsPlayerProjectile.h"

namespace js
{
	Monster::Monster()
	{
		Initialize();
	}
	Monster::Monster(Pos pos)
	{
		Initialize();
		SetPos(pos);
	}
	Monster::~Monster()
	{
	}

	void Monster::Initialize()
	{
		SetType(eColliderLayer::Monster);
		Creature::Initialize();
		SetAnimator();
	}
	void Monster::SetAnimator()
	{
		// Imp Aniamtion
		mAnimator->CreateAnimation(L"ImpIdleR", mSpriteImage, Pos(0.f, 0.f), Size(17.f, 21.f)
			, Vector2(0.f, 0.f), 1, 0.1f);
		mAnimator->CreateAnimation(L"ImpIdleL", mSpriteImage, Pos(0.f, 21.f), Size(17.f, 21.f)
			, Vector2(0.f, 0.f), 1, 0.1f);

		mAnimator->CreateAnimation(L"ImpMoveR", mSpriteImage, Pos(0.f, 42.f), Size(18.0f, 25.f)
			, Vector2(0.f, 0.f), 6, 0.1f);
		mAnimator->CreateAnimation(L"ImpMoveL", mSpriteImage, Pos(0.f, 67.f), Size(18.0f, 25.f)
			, Vector2(0.f, 0.f), 6, 0.1f);

		mAnimator->CreateAnimation(L"ImpTeleportR", mSpriteImage, Pos(0.f, 92.f), Size(17.f, 21.f)
			, Vector2(0.f, 0.f), 3, 0.1f);
		mAnimator->CreateAnimation(L"ImpTeleportL", mSpriteImage, Pos(0.f, 113.f), Size(17.f, 21.f)
			, Vector2(0.f, 0.f), 3, 0.1f);

		mAnimator->CreateAnimation(L"ImpAttackR", mSpriteImage, Pos(0.f, 134.f), Size(33.f, 21.f)
			, Vector2(-7.f, 0.f), 11, 0.1f);
		mAnimator->CreateAnimation(L"ImpAttackL", mSpriteImage, Pos(0.f, 155.f), Size(33.f, 21.f)
			, Vector2(-10.f, 0.f), 11, 0.1f);

		mAnimator->CreateAnimation(L"ImpDeathR", mSpriteImage, Pos(0.f, 176.f), Size(26.0f, 21.f)
			, Vector2(-5.f, 0.f), 8, 0.1f);
		mAnimator->CreateAnimation(L"ImpDeathL", mSpriteImage, Pos(0.f, 197.f), Size(26.0f, 21.f)
			, Vector2(-5.f, 0.f), 8, 0.1f);
	}
	void Monster::ImpInit()
	{
		// 충돌체
		SetMonsterStat(310.0f, 0, 0, 13, 1, 600, 16.0f);

		// collider
		mBodyCollider->SetSize(Size(20.f, 25.f) * GetScale());
		mBodyCollider->SetOffset(Vector2(8.f, 13.f));
		mFootCollider->SetSize(Size(15, 5) * GetScale());
		mFootCollider->SetOffset(Vector2(8, 38.f));

	}
	void Monster::ParentInit()
	{
		// 충돌체
	}
	
	void Monster::Tick()
	{
		Creature::Tick();


		switch (mState)
		{

		}
	}
	void Monster::Render(HDC hdc)
	{
		Creature::Render(hdc);
	}

	void Monster::Stay()
	{
	}

	void Monster::Chase()
	{
	}

	void Monster::Skill()
	{
	}

	void Monster::Stun()
	{
	}

	void Monster::Death()
	{
	}
	
	void Monster::OnCollisionEnter(Collider* other)
	{
		GameObject* collisionObj = other->GetOwner();
		eColliderLayer type = collisionObj->GetType();

		// 벽에 닿음
		if (type == eColliderLayer::Platform)
		{
			// 나아가지 못하게 막기
			BodyCollision(collisionObj);
		}
	}
	void Monster::OnCollisionStay(Collider* other)
	{
	}
	void Monster::OnCollisionExit(Collider* other)
	{
	}

	// damage, stagger, power
	void Monster::SelfHit(GameObject* attaker, float damage, eStagger stagger, float power)
	{
		SelfDamaged(damage);
		SelfKnockBack(attaker->GetDir().x, stagger, power);
	}

	// damage
	void Monster::SelfDamaged(float damage)
	{
		// 방어력 계산해서 피 까기
		float finalDamage = damage - mHealthStat->defance;

		// 최소 피해량
		if (1 > damage - mHealthStat->defance)
			finalDamage = 1;
		
		mHealthStat->curHP -= finalDamage;
	}

	//stagger, power
	void Monster::SelfKnockBack(float dir, eStagger stagger, float power)
	{
		// 저항력이 관통력보다 낮은 경우
		if (stagger >= mResistance)		// 관통이 0이고 저항력이 0이면 넉백
		{
			// 넉백
			Vector2 knockBack = mRigidbody->GetVelocity();
			knockBack.x = dir * power * 2.5f;
			mRigidbody->SetVelocity(knockBack);

			// 관통력이 쌔면 기절
			if (eStagger::Heave == stagger)
				SelfStun(power);
		}
	}

	// power
	void Monster::SelfStun(float power)
	{
		// power에 따라서 기절시간이 달라짐
	}
}