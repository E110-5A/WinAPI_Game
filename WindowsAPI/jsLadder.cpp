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
		
		// Climb ���·� �����

		// Idle ���·� �����

	}
	void Ladder::SetPlayerPos(Player* player)
	{
		// �÷��̾� Pos.x ����
	}
	void Ladder::OnCollisionEnter(Collider* other)
	{
		
	}
	void Ladder::OnCollisionStay(Collider* other)
	{
		// �浹�� ����� �÷��̾ �ƴ϶�� return
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