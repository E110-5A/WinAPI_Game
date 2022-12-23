#include "jsMonster.h"

// �Ŵ���
#include "jsCamera.h"
// ���ҽ�
#include "jsResources.h"
#include "jsImage.h"

// ������Ʈ
#include "jsCollider.h"
#include "jsAnimator.h"
#include "jsRigidbody.h"

// ������Ʈ
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

		// ���� ����
		if (type == eColliderLayer::Platform)
		{
			// ���ư��� ���ϰ� ����
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
		// ���� ����ؼ� �� ���
		float finalDamage = damage - mHealthStat.defance;

		// �ּ� ���ط�
		if (1 > damage - mHealthStat.defance)
			finalDamage = 1;
		
		mHealthStat.curHP -= finalDamage;
	}

	//stagger, power
	void Monster::SelfKnockBack(float dir, eStagger stagger, float power)
	{
		// ���׷��� ����º��� ���� ���
		if (stagger >= mResistance)		// ������ 0�̰� ���׷��� 0�̸� �˹�
		{
			// �˹�
			Vector2 knockBack = mRigidbody->GetVelocity();
			knockBack.x = dir * power * 2.5f;
			mRigidbody->SetVelocity(knockBack);

			// ������� �ظ� ����
			if (eStagger::Heave == stagger)
				SelfStun(power);
		}
	}

	// power
	void Monster::SelfStun(float power)
	{
		// power�� ���� �����ð��� �޶���
	}
}