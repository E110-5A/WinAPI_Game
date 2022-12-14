#include "jsGround.h"

// component
#include "jsCollider.h"
#include "jsRigidbody.h"

// object
#include "jsCreature.h"
#include "jsGroundCheck.h"

namespace js
{
	Ground::Ground()
	{
		Initialize();
	}
	Ground::Ground(Pos pos)
	{
		Initialize();
		SetPos(pos);
	}
	Ground::~Ground()
	{
	}

	void Ground::Initialize()
	{
		SetType(eColliderLayer::Ground);
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Size(64.0f, 64.0f));
	}
	void Ground::Tick()
	{
		GameObject::Tick();
	}
	void Ground::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Ground::OnCollisionEnter(Collider* other)
	{
		GameObject* tempObj = other->GetOwner();
		
		if (eColliderLayer::GroundCheck != tempObj->GetType())
			WallProcess(tempObj);
	}
	void Ground::OnCollisionStay(Collider* other)
	{
		GameObject* tempObj = other->GetOwner();

		if (eColliderLayer::GroundCheck != tempObj->GetType())
			WallProcess(tempObj);
	}
	void Ground::OnCollisionExit(Collider* other)
	{
	}

	void Ground::WallProcess(GameObject* other)
	{
		Rigidbody* rigidbody = other->GetComponent<Rigidbody>();
		Vector2 velocity = rigidbody->GetVelocity();
		velocity.x = GetDir().x * 20.0f;
		rigidbody->SetVelocity(velocity);
	}
}