#include "jsCollisionCheck.h"

// component
#include "jsCollider.h"

// object
#include "jsCreature.h"


namespace js
{
	CollisionCheck::CollisionCheck()
		: mCollider(nullptr)
		, mOwner(nullptr)
	{
	}
	CollisionCheck::~CollisionCheck()
	{
	}
	void CollisionCheck::Initialize()
	{
		mCollider = AddComponent<Collider>();
	}
	void CollisionCheck::Tick()
	{
		GameObject::Tick();
		SetPos(mOwner->GetPos());
	}
	void CollisionCheck::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void CollisionCheck::OnCollisionEnter(Collider* other)
	{
	}
	void CollisionCheck::OnCollisionStay(Collider* other)
	{
	}
	void CollisionCheck::OnCollisionExit(Collider* other)
	{
	}
}