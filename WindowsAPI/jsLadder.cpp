#include "jsLadder.h"

// manager
#include "jsInput.h"

// component
#include "jsCollider.h"
#include "jsRigidbody.h"

// object
#include "jsPlayer.h"

namespace js
{
	Ladder::Ladder()
	{
		Initialize();
	}
	Ladder::Ladder(Pos pos)
	{
		SetPos(pos);
		Initialize();
	}
	Ladder::~Ladder()
	{
	}
	void Ladder::Initialize()
	{
		CollisionBlock::Initialize();
	}

	void Ladder::Tick()
	{
		CollisionBlock::Tick();
	}
	void Ladder::Render(HDC hdc)
	{
		CollisionBlock::Render(hdc);
	}
	
	void Ladder::OnCollisionEnter(Collider* other)
	{		
	}
	void Ladder::OnCollisionStay(Collider* other)
	{
		// 플레이어만 충돌가능함
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		
		if ((KEY_DOWN(eKeyCode::UP) || KEY_DOWN(eKeyCode::DOWN)) && ePlayerState::Climb != player->GetState())
		{
			player->SetState(ePlayerState::Climb);
		}
		// Climb 상태라면
		Process(player);
	}

	void Ladder::OnCollisionExit(Collider* other)
	{
		if (eColliderLayer::Player != other->GetOwner()->GetType())
			return;
		Player* player = dynamic_cast<Player*>(other->GetOwner());

		if (ePlayerState::Climb == player->GetState())
		{
			player->SetState(ePlayerState::Idle);
			player->GetComponent<Rigidbody>()->SetGround(false);
		}
	}

	void Ladder::Process(GameObject* target)
	{
		Player* player = dynamic_cast<Player*>(target);
		if (ePlayerState::Climb == player->GetState())
		{
			// 플레이어의 x 위치를 내 위치로 가져옴
			Vector2 playerPos = player->GetPos();
			Vector2 ladderPos = GetPos();
			ladderPos.x += mCollider->GetSize().x / 3 * 2;
			playerPos.x = ladderPos.x;
			player->SetPos(playerPos);
		}
	}
}