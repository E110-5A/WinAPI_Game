#include "jsFoot.h"

// manager
#include "jsInput.h"

// component
#include "jsCollider.h"
#include "jsRigidbody.h"
#include "jsAnimator.h"

// object
#include "jsCreature.h"
#include "jsPlayer.h"
#include "jsLadder.h"
#include "jsPlatform.h"

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
		SetType(eColliderLayer::Foot);
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
		// Player State :: Climb 예외처리
		if (eColliderLayer::Platform == other->GetOwner()->GetType())
		{
			PlatformCollision(other);
		}
		
	}

	void Foot::OnCollisionStay(Collider* other)
	{
		// Player State :: Climb 예외처리
		if (eColliderLayer::Ladder == other->GetOwner()->GetType())
		{
			ClimbDown(other);
		}
	}

	void Foot::OnCollisionExit(Collider* other)
	{
		
	}


	void Foot::ClimbDown(Collider* other)
	{
		Ladder* ladder = dynamic_cast<Ladder*>(other->GetOwner());
		Player* player = dynamic_cast<Player*>(mOwner);
		if (nullptr != player)
		{
			// 꼭대기에서 내려가는 경우
			if (KEY_DOWN(eKeyCode::DOWN) && ePlayerState::Climb != player->GetState() && false == ladder->IsPlayerCollision())
			{
				player->SetState(ePlayerState::Climb);
				player->SetGround(true);
				player->JumpCountReset();
				ladder->PullPlayer(player);
			}
		}
	}

	void Foot::PlatformCollision(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(mOwner);
		if (nullptr != player)
		{
			// 사다리 타다가 땅에 닿은 경우
			if (ePlayerState::Climb == player->GetState() && false == player->GetBlocking())
			{
				player->SetState(ePlayerState::Idle);
				if (Vector2::Right == player->GetDir())
					player->GetComponent<Animator>()->Play(L"PIdleR");
				else
					player->GetComponent<Animator>()->Play(L"PIdleL");
				player->SetGround(true);
			}
		}
	}
}