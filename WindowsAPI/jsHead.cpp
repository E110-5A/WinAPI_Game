#include "jsHead.h"

// component
#include "jsCollider.h"
#include "jsRigidbody.h"
#include "jsAnimator.h"

// collider
#include "jsCreature.h"

#include "jsPlayer.h"

namespace js
{
	Head::Head()
	{
		Initialize();
	}
	Head::~Head()
	{
	}

	void Head::Initialize()
	{
		CollisionCheck::Initialize();
		SetType(eColliderLayer::Head);
	}
	void Head::Tick()
	{
		CollisionCheck::Tick();
	}
	void Head::Render(HDC hdc)
	{
		CollisionCheck::Render(hdc);
	}

	void Head::OnCollisionEnter(Collider* other)
	{
		// õ�忡 �Ӹ� ������ ����
		Process();
	}
	void Head::OnCollisionStay(Collider* other)
	{
	}
	void Head::OnCollisionExit(Collider* other)
	{
	}
	void Head::Process()
	{
		mOwner->GetRigidbody()->EraseVelocity(Vector2::Down, mOwner->GetRigidbody()->GetVelocity());
	}
}