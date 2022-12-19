#include "jsCreature.h"

// component
#include "jsCollider.h"
#include "jsAnimator.h"
#include "jsRigidbody.h"

// object
#include "jsObject.h"
#include "jsGroundCheck.h"
#include "jsCeilingCheck.h"

namespace js
{
	Creature::Creature()
		: mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mHeadCollider(nullptr)
		, mBodyCollider(nullptr)
		, mFootCollider(nullptr)
		, mHealthStat{}
		, mOffenceStat{}
		, mUtilityStat{}
		, mResistance{}
		, mFootObject(nullptr)
		, mHeadObject(nullptr)
		, mSpriteImage(nullptr)
	{
	}
	Creature::Creature(Pos pos)
		: mAnimator(nullptr)
		, mRigidbody(nullptr)
		, mHeadCollider(nullptr)
		, mBodyCollider(nullptr)
		, mFootCollider(nullptr)
		, mHealthStat{}
		, mOffenceStat{}
		, mUtilityStat{}
		, mResistance{}
		, mFootObject(nullptr)
		, mHeadObject(nullptr)
		, mSpriteImage(nullptr)
	{
	}
	Creature::~Creature()
	{
	}

	void Creature::Initialize()
	{
		SetComponent();
	}

	void Creature::Tick()
	{
		GameObject::Tick();
	}
	void Creature::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Creature::OnCollisionEnter(Collider* other)
	{
	}
	void Creature::OnCollisionStay(Collider* other)
	{
	}
	void Creature::OnCollisionExit(Collider* other)
	{
	}

	void Creature::SetComponent()
	{
		mAnimator = AddComponent<Animator>();
		mBodyCollider = AddComponent<Collider>();
		mRigidbody = AddComponent<Rigidbody>();

		// �� �浹 üũ ������Ʈ ���� �� �Ҵ�
		mFootObject = object::Instantiate<GroundCheck>(eColliderLayer::CollisionCheck);
		mFootObject->SetOwner(this);
		mFootCollider = mFootObject->AddComponent<Collider>();
		mHeadObject = object::Instantiate<CeilingCheck>(eColliderLayer::CollisionCheck);
		mHeadObject->SetOwner(this);
		mHeadCollider = mHeadObject->AddComponent<Collider>();
	}

	void Creature::SelfHit(GameObject* attaker, float damage, eStagger stagger, float power)
	{
		SelfDamaged(damage);
		SelfKnockBack(attaker->GetDir().x, stagger, power);
	}
	void Creature::SelfDamaged(float damage)
	{
		// ���� ����ؼ� �� ���
		float finalDamage = damage - mHealthStat.defance;

		// �ּ� ���ط�
		if (1 > damage - mHealthStat.defance)
			finalDamage = 1;

		mHealthStat.curHP -= finalDamage;
	}
	void Creature::SelfKnockBack(float dir, eStagger stagger, float power)
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
	// �̿�
	void Creature::SelfStun(float power)
	{
	}
}