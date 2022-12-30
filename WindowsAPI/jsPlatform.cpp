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
		
		// 바닥 <-> 발바닥 충돌
		if (eColliderLayer::Foot == target->GetType())
		{
			// 대상의 Ground상태 변경, 점프카운트 초기화, Climb 예외처리
			TargetSetGround(target, true);
			TargetJumpCountReset(target);

			// 플레이어가 충돌한 경우, 몬스터 스폰지점을 해당 플랫폼으로 변경
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

		// 바닥 <-> 발바닥 충돌
		if (eColliderLayer::Foot == target->GetType())
		{
			// Ground = false (if state::Climb, ignore)
			TargetSetGround(target, false);
		}
	}

	void Platform::TargetSetGround(GameObject* foot, bool isGround)
	{
		// Target 형변환
		Creature* target = dynamic_cast<Foot*>(foot)->GetOwner();
		
		// Climb 예외처리
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
		// Target 형변환
		Creature* target = dynamic_cast<Foot*>(foot)->GetOwner();
		target->JumpCountReset();
	}

}