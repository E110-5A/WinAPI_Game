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

		// 잠시 유지하다 사라지게 만듦
		if (0.2 <= mDeltaTime)
		{
			InActive();
		}
	}



	void MonsterAttack::OnCollisionEnter(Collider* other)
	{
		GameObject* target = other->GetOwner();
		// 플레이어의 Damaged 호출?
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
		// 활성화
		SetAble(true);

		// 공격 범위(크기) 설정
		mRange = mOwner->GetOffence()->range;
		Collider* onwerCollider = mOwner->GetComponent<Collider>();
		float colliderSizeY = onwerCollider->GetSize().y;
		mCollider->SetSize(Size(mRange, colliderSizeY));

		// 공격력
		mInfo.damage = mOwner->GetOffence()->damage;
		
		// 위치값 갱신
		SetPos(mOwner->GetPos());
		SetDir(mOwner->GetDir());
	}
}