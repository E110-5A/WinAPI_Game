#include "jsGround.h"
#include "jsCollider.h"
#include "jsRigidbody.h"

#include "jsGroundCheck.h"

namespace js
{
	Ground::Ground()
	{
		Initialize();
	}
	Ground::Ground(Pos pos)
	{
		Initialize();
		SetPos(pos);
	}
	Ground::~Ground()
	{
	}

	void Ground::Initialize()
	{
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Size(64.0f, 64.0f));
	}
	void Ground::Tick()
	{
		GameObject::Tick();
	}
	void Ground::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Ground::OnCollisionEnter(Collider* other)
	{
		// 충돌한 레이어가 바닥체크 오브젝트면
		GameObject* tempObj = other->GetOwner();
		if (eColliderLayer::GroundCheck == tempObj->GetType())
		{
			// 해당 오브젝트 오너의 Rigidbody 값을 변경
			GroundCheck* groundCheck = dynamic_cast<GroundCheck*>(tempObj);
			GameObject* ownerObj = groundCheck->GetOwner();
			ownerObj->GetComponent<Rigidbody>()->SetGround(true);



			// 대상의 y위치와 내 y위치를 뺀 절댓값 길이
			float fLen = fabs(other->GetPos().y - GetComponent<Collider>()->GetPos().y);
			// 맞닿아있을 때, 대상의 y크기 절반과 내 y크기 절반을 더한 값
			float fSize = other->GetSize().y / 2.0f + GetComponent<Collider>()->GetSize().y / 2.0f;

			// 땅을 파고들었다던가 해서.. 길이가 안맞는다면?
			if (fLen < fSize)
			{
				// 대상의 y위치를 변동값 만큼 위로 옮기기
				Vector2 curPos = ownerObj->GetPos();
				curPos.y -= (fSize - fLen) - 1.0f;
				ownerObj->SetPos(curPos);
			}
		}
		else
		{
			Rigidbody* rigidbody = tempObj->GetComponent<Rigidbody>();
			Vector2 velocity = rigidbody->GetVelocity();
			velocity.x = -GetDir().x * 150.0f;
			rigidbody->SetVelocity(velocity);
		}


		

	}
	void Ground::OnCollisionStay(Collider* other)
	{
	}
	void Ground::OnCollisionExit(Collider* other)
	{
	}
}