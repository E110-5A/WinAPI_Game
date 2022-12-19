#include "jsFoot.h"

// component
#include "jsCollider.h"
#include "jsRigidbody.h"
#include "jsAnimator.h"

// collider
#include "jsCreature.h"

#include "jsPlayer.h"

namespace js
{

	Foot::Foot()
	{
		Initialize();
	}
	Foot::~Foot()
	{
	}

	void Foot::Initialize()
	{
		CollisionCheck::Initialize();
	}
	void Foot::Tick()
	{
		CollisionCheck::Tick();
	}
	void Foot::Render(HDC hdc)
	{
		CollisionCheck::Render(hdc);
	}

	void Foot::OnCollisionEnter(Collider* other)
	{
		// rigidbody->ground 상태 변경
		eColliderLayer objLayer = other->GetOwner()->GetType();
		if (eColliderLayer::Platform == objLayer)
			mOwner->GetComponent<Rigidbody>()->SetGround(true);

		// climb 예외처리
		Player* player = dynamic_cast<Player*>(mOwner);
		if (nullptr != player && ePlayerState::Climb == player->GetState() && false == player->GetBlocking())
		{
			player->SetState(ePlayerState::Idle);
			if (Vector2::Right == player->GetDir())
				player->GetComponent<Animator>()->Play(L"PIdleR");
			else
				player->GetComponent<Animator>()->Play(L"PIdleL");
		}

		// 점프 카운트 회복
		mOwner->GetUtility().curJumpCount = 0;

	}

	void Foot::OnCollisionStay(Collider* other)
	{
	}

	void Foot::OnCollisionExit(Collider* other)
	{
		// Climb 상태라면 땅에서 벗어나도 중력이 적용되지 않음

		Player* player = dynamic_cast<Player*>(mOwner);
		if (nullptr != player && ePlayerState::Climb == player->GetState())
			return;

		eColliderLayer objLayer = other->GetOwner()->GetType();
		if (eColliderLayer::Platform == objLayer)
			mOwner->GetComponent<Rigidbody>()->SetGround(isGround);
	}


	void Foot::Process()
	{		
	}
}