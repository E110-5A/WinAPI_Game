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
		: mImage(nullptr)
	{
	}
	Monster::Monster(Pos pos)
		: mImage(nullptr)
	{
	}
	Monster::~Monster()
	{
	}

	void Monster::Initialize()
	{
		SetType(eColliderLayer::Monster);
	}
	void Monster::Tick()
	{
	}
	void Monster::Render(HDC hdc)
	{
	}

	

	void Monster::OnCollisionEnter(Collider* other)
	{
	}
	void Monster::OnCollisionStay(Collider* other)
	{
	}
	void Monster::OnCollisionExit(Collider* other)
	{
	}


	void Monster::Hit(GameObject* attaker)
	{
		SelfKnockBack(attaker);
		SelfDamaged(attaker);
	}

	void Monster::SelfDamaged(GameObject* attaker)
	{
		
	}

	void Monster::SelfKnockBack(GameObject* attaker)
	{
		Vector2 velocity = mRigidbody->GetVelocity();
		velocity.x = attaker->GetDir().x * 100.0f;
		mRigidbody->SetVelocity(velocity);
	}

	void Monster::SelfStrun()
	{
	}
}