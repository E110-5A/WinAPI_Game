#include "jsPlatform.h"

// manager
#include "jsGameManager.h"

// component
#include "jsCollider.h"
#include "jsRigidbody.h"

// object
#include "jsCreature.h"
#include "jsFoot.h"
#include "jsPlayer.h"

namespace js
{
	Platform::Platform()
	{
		Initialize();
	}
	Platform::Platform(Pos pos)
	{
		Initialize();
		SetPos(pos);
	}
	Platform::~Platform()
	{
	}

	void Platform::Initialize()
	{
		CollisionBlock::Initialize();
	}
	void Platform::Tick()
	{
		CollisionBlock::Tick();
	}
	void Platform::Render(HDC hdc)
	{
		CollisionBlock::Render(hdc);
	}

	void Platform::OnCollisionEnter(Collider* other)
	{
		GameObject* target = other->GetOwner();
		
		// �ٴ� <-> �߹ٴ� �浹
		if (eColliderLayer::Foot == target->GetType())
		{
			// ����� Ground���� ����, ����ī��Ʈ �ʱ�ȭ, Climb ����ó��
			TargetSetGround(target, true);
			TargetJumpCountReset(target);

			// �÷��̾ �浹�� ���, ���� ���������� �ش� �÷������� ����
			if (eColliderLayer::Player == dynamic_cast<Foot*>(target)->GetOwner()->GetType())
				GameManager::SetSpawnPlatform(this);
		}
	}
	void Platform::OnCollisionStay(Collider* other)
	{
		GameObject* tempObj = other->GetOwner();
	}
	void Platform::OnCollisionExit(Collider* other)
	{
		GameObject* target = other->GetOwner();

		// �ٴ� <-> �߹ٴ� �浹
		if (eColliderLayer::Foot == target->GetType())
		{
			// Ground = false (if state::Climb, ignore)
			TargetSetGround(target, false);
		}
	}

	void Platform::TargetSetGround(GameObject* foot, bool isGround)
	{
		// Target ����ȯ
		Creature* target = dynamic_cast<Foot*>(foot)->GetOwner();
		
		// Climb ����ó��
		if (eColliderLayer::Player == target->GetType())
		{
			if (ePlayerState::Climb != dynamic_cast<Player*>(target)->GetState())
			{
				// Ground setting
				target->GetRigidbody()->SetGround(isGround);
			}
		}
		if (eColliderLayer::Monster == target->GetType())
		{
			target->GetRigidbody()->SetGround(isGround);
		}
		
	}

	void Platform::TargetJumpCountReset(GameObject* foot)
	{
		// Target ����ȯ
		Creature* target = dynamic_cast<Foot*>(foot)->GetOwner();
		target->JumpCountReset();
	}

}