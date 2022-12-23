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
	}
	Monster::Monster(Pos pos)
	{
	}
	Monster::~Monster()
	{
	}

	void Monster::Initialize()
	{
		SetType(eColliderLayer::Monster);
	}
	void Monster::InitComponent()
	{
		Creature::InitComponent();
	}
	void Monster::Tick()
	{
		Creature::Tick();
	}
	void Monster::Render(HDC hdc)
	{
		Creature::Render(hdc);
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
		float finalDamage = damage - mHealthStat.defance;

		// 최소 피해량
		if (1 > damage - mHealthStat.defance)
			finalDamage = 1;
		
		mHealthStat.curHP -= finalDamage;
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