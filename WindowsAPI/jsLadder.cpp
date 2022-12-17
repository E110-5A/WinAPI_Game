#include "jsLadder.h"

// manager
#include "jsInput.h"

// component
#include "jsCollider.h"

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
		EventObject::Initialize();
	}

	void Ladder::Tick()
	{
		EventObject::Tick();
	}
	void Ladder::Render(HDC hdc)
	{
		EventObject::Render(hdc);
	}
	void Ladder::SetPlayerState(Player* player)
	{
		if (ePlayerState::Climb != player->GetState())
		{
			int a = 0;
		}
		
		// Climb 상태로 만들기

		// Idle 상태로 만들기

	}
	void Ladder::SetPlayerPos(Player* player)
	{
		// 플레이어 Pos.x 보정
	}
	void Ladder::OnCollisionEnter(Collider* other)
	{
		
	}
	void Ladder::OnCollisionStay(Collider* other)
	{
		// 충돌한 대상이 플레이어가 아니라면 return
		if (eColliderLayer::Player != other->GetOwner()->GetType())
			return;

		Player* target = dynamic_cast<Player*>(other->GetOwner());

		if (KEY_DOWN(eKeyCode::UP) || KEY_DOWN(eKeyCode::DOWN))
		{
			SetPlayerState(target);
		}		
	}
	void Ladder::OnCollisionExit(Collider* other)
	{
	}
}