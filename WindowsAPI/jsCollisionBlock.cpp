#include "jsCollisionBlock.h"

// component
#include "jsCollider.h"

namespace js
{
	CollisionBlock::CollisionBlock()
		: mCollider(nullptr)
	{
	}
	CollisionBlock::CollisionBlock(Pos pos)
		: mCollider(nullptr)
	{
	}
	CollisionBlock::~CollisionBlock()
	{
	}

	void CollisionBlock::Initialize()
	{
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Size(GRID_SIZE, GRID_SIZE));
	}
	void CollisionBlock::Tick()
	{
		GameObject::Tick();
	}
	void CollisionBlock::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void CollisionBlock::OnCollisionEnter(Collider* other)
	{		
	}
	void CollisionBlock::OnCollisionStay(Collider* other)
	{		
	}
	void CollisionBlock::OnCollisionExit(Collider* other)
	{
	}
}