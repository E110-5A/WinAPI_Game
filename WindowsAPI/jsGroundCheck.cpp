#include "jsGroundCheck.h"

// component
#include "jsCollider.h"
#include "jsRigidbody.h"
#include "jsAnimator.h"

// collider
#include "jsCreature.h"

#include "jsPlayer.h"

namespace js
{

	GroundCheck::GroundCheck()
		: mOwner(nullptr)
		, mCollider(nullptr)
	{
		SetType(eColliderLayer::CollisionCheck);
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
		Player* player = dynamic_cast<Player*>(mOwner);
		GroundProcess(other, true);

		// 1) ���� ���� ���,	 2)���� �ε�ģ ���°� �ƴ϶��		Climb -> Idle
		if (nullptr != player && ePlayerState::Climb == player->GetState() && false == player->GetBlocking())
		{
			player->SetState(ePlayerState::Idle);
			if (Vector2::Right == player->GetDir())
				player->GetComponent<Animator>()->Play(L"PIdleR");
			else
				player->GetComponent<Animator>()->Play(L"PIdleL");
		}

		// ���� ī��Ʈ ȸ��
		mOwner->GetUtility().curJumpCount = 0;
	}

	void GroundCheck::OnCollisionStay(Collider* other)
	{
	}

	void GroundCheck::OnCollisionExit(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(mOwner);

		// Climb ���¶�� ������ ����� �߷��� ������� ����
		if (nullptr != player && ePlayerState::Climb == player->GetState())
			return;
		
		GroundProcess(other, false);
	}

	void GroundCheck::GroundProcess(Collider* other, bool isGround)
	{
		eColliderLayer objLayer = other->GetOwner()->GetType();
		if (eColliderLayer::Platform == objLayer)
			mOwner->GetComponent<Rigidbody>()->SetGround(isGround);
	}
}