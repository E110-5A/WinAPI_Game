#include "jsLadder.h"

// manager
#include "jsInput.h"

// component
#include "jsCollider.h"
#include "jsRigidbody.h"
#include "jsAnimator.h"

// object
#include "jsPlayer.h"
#include "jsFoot.h"

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
		// Climb�� �ƴ� ���¿��� UPŰ�� ���� ���
		if (eColliderLayer::Player == other->GetOwner()->GetType())
		{
			BodyCollision(other);
		}
	}

	void Ladder::OnCollisionExit(Collider* other)
	{
		if (eColliderLayer::Foot == other->GetOwner()->GetType())
		{
			FootEscapeLadder(other);
		}
		if (eColliderLayer::Player == other->GetOwner()->GetType())
		{
			mIsBodyCollision = false;
		}
	}


	void Ladder::PullPlayer(GameObject* target)
	{
		Player* player = dynamic_cast<Player*>(target);
		if (ePlayerState::Climb == player->GetState())
		{
			// �÷��̾��� x ��ġ�� �� ��ġ�� ������
			Vector2 playerPos = player->GetPos();
			Vector2 ladderPos = GetPos();
			ladderPos.x += mCollider->GetSize().x / 3 * 2;
			playerPos.x = ladderPos.x;
			player->SetPos(playerPos);
		}
	}

	void Ladder::BodyCollision(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (nullptr != player)
		{
			mIsBodyCollision = true;
			if (KEY_DOWN(eKeyCode::UP) && ePlayerState::Climb != player->GetState())
			{
				player->SetState(ePlayerState::Climb);
				player->SetGround(true);
				player->JumpCountReset();
			}
			// �������
			PullPlayer(player);
		}
	}
	void Ladder::FootEscapeLadder(Collider* other)
	{
		
		Foot* foot = dynamic_cast<Foot*>(other->GetOwner());
		Player* player = dynamic_cast<Player*>(foot->GetOwner());

		// Climb ���¿��� ��� ��� (State -> Stay, Ground -> false
		if (ePlayerState::Climb == player->GetState())
		{
			if (Vector2::Right == player->GetDir())
				player->GetComponent<Animator>()->Play(L"PIdleR");
			else
				player->GetComponent<Animator>()->Play(L"PIdleL");
			player->SetState(ePlayerState::Idle);
			player->GetRigidbody()->SetGround(false);
		}
	}
}