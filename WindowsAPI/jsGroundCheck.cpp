#include "jsGroundCheck.h"

// component
#include "jsCollider.h"
#include "jsRigidbody.h"

// collider
#include "jsCreature.h"

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
		GameObject* tempObj = other->GetOwner();
		SetGround(tempObj, true);

		// 점프 카운트 회복
		mOwner->GetUtility().curJumpCount = 0;
	}

	void GroundCheck::OnCollisionStay(Collider* other)
	{
	}

	void GroundCheck::OnCollisionExit(Collider* other)
	{
		GameObject* tempObj = other->GetOwner();
		SetGround(tempObj, false);
	}
	void GroundCheck::SetGround(GameObject* other, bool isGround)
	{
		eColliderLayer tempObj = other->GetType();
		if (eColliderLayer::Platform == tempObj)
			mOwner->GetComponent<Rigidbody>()->SetGround(isGround);
	}
}