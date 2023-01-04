#include "jsMonsterAttack.h"

// manager
#include "jsTime.h"

// component
#include "jsCollider.h"

// object
#include "jsMonster.h"
#include "jsPlayer.h"

namespace js
{
	MonsterAttack::MonsterAttack()
	{
	}
	MonsterAttack::MonsterAttack(Creature* owner)
	{
		mOwner = owner;
		mCollider = AddComponent<Collider>();
		SetAble(false);
	}
	MonsterAttack::~MonsterAttack()
	{
	}
	void MonsterAttack::Tick()
	{
		if (!mAble)
			return;
		GameObject::Tick();

		Process();
	}
	void MonsterAttack::Render(HDC hdc)
	{
		if (!mAble)
			return;
		GameObject::Render(hdc);
	}
	void MonsterAttack::Process()
	{
		mDeltaTime += Time::GetDeltaTime();

		// ��� �����ϴ� ������� ����
		if (0.2 <= mDeltaTime)
		{
			InActive();
		}
	}



	void MonsterAttack::OnCollisionEnter(Collider* other)
	{
		GameObject* target = other->GetOwner();
		// �÷��̾��� Damaged ȣ��?
		if (eColliderLayer::Player == target->GetType())
		{
			dynamic_cast<Player*>(target)->SelfHit(this, mInfo.damage, eStagger::Light);
		}
	}
	void MonsterAttack::OnCollisionStay(Collider* other)
	{
	}
	void MonsterAttack::OnCollisionExit(Collider* other)
	{
	}
	void MonsterAttack::Active()
	{
		// Ȱ��ȭ
		SetAble(true);

		// ���� ����(ũ��) ����
		mRange = mOwner->GetOffence()->range;
		Collider* onwerCollider = mOwner->GetComponent<Collider>();
		float colliderSizeY = onwerCollider->GetSize().y;
		mCollider->SetSize(Size(mRange, colliderSizeY));

		// ���ݷ�
		mInfo.damage = mOwner->GetOffence()->damage;
		
		// ��ġ�� ����
		SetPos(mOwner->GetPos());
		SetDir(mOwner->GetDir());
	}
}