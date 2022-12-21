#include "jsCreature.h"

// component
#include "jsCollider.h"
#include "jsAnimator.h"
#include "jsRigidbody.h"

// object
#include "jsObject.h"
#include "jsFoot.h"
#include "jsHead.h"

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
		mFootObject->Tick();
		mHeadObject->Tick();
	}
	void Creature::Render(HDC hdc)
	{
		GameObject::Render(hdc);
		mFootObject->Render(hdc);
		mHeadObject->Render(hdc);
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
		mRigidbody = AddComponent<Rigidbody>();

		// body
		mBodyCollider = AddComponent<Collider>();
		// foot
		mFootObject = object::Instantiate<Foot>(eColliderLayer::Foot);
		mFootObject->SetOwner(this);
		mFootCollider = mFootObject->GetComponent<Collider>();
		// head
		mHeadObject = object::Instantiate<Head>(eColliderLayer::Head);
		mHeadObject->SetOwner(this);
		mHeadCollider = mHeadObject->GetComponent<Collider>();
	}

	void Creature::BodyCollision(GameObject* other)
	{
		// ���� ���� ��ġ ���ϱ�
		Vector2 targetPos = other->GetPos();
		Vector2 myPos = GetPos();

		// ������� �� ���� ã��
		Vector2 wallLocationDir = myPos - targetPos;
		if (0 < wallLocationDir.x)					// x�� ����� ��� ����ġ�� �� ����
			wallLocationDir = Vector2::Left;
		else
			wallLocationDir = Vector2::Right;

		// ���� ���� ��� x �ӷ��� 0���� �����
		if (wallLocationDir == mDir)
		{
			mRigidbody->EraseVelocity(wallLocationDir, mRigidbody->GetVelocity());
		}
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