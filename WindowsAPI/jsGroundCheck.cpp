#include "jsGroundCheck.h"

#include "jsCollider.h"

namespace js
{

	GroundCheck::GroundCheck()
		: mOwner(nullptr)
		, mCollider(nullptr)
	{
		SetType(eColliderLayer::GroundCheck);
	}

	GroundCheck::~GroundCheck()
	{
	}

	void GroundCheck::Tick()
	{
		if (nullptr == mCollider)
			mCollider = GetComponent<Collider>();
		
		SetPos(mOwner->GetPos());

		GameObject::Tick();
	}

	void GroundCheck::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void GroundCheck::OnCollisionEnter(Collider* other)
	{
	}

	void GroundCheck::OnCollisionStay(Collider* other)
	{
	}

	void GroundCheck::OnCollisionExit(Collider* other)
	{
	}
}