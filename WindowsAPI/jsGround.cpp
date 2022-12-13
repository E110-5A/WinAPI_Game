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
		// �浹�� ���̾ �ٴ�üũ ������Ʈ��
		GameObject* tempObj = other->GetOwner();
		if (eColliderLayer::GroundCheck == tempObj->GetType())
		{
			// �ش� ������Ʈ ������ Rigidbody ���� ����
			GroundCheck* groundCheck = dynamic_cast<GroundCheck*>(tempObj);
			GameObject* ownerObj = groundCheck->GetOwner();
			ownerObj->GetComponent<Rigidbody>()->SetGround(true);



			// ����� y��ġ�� �� y��ġ�� �� ���� ����
			float fLen = fabs(other->GetPos().y - GetComponent<Collider>()->GetPos().y);
			// �´������ ��, ����� yũ�� ���ݰ� �� yũ�� ������ ���� ��
			float fSize = other->GetSize().y / 2.0f + GetComponent<Collider>()->GetSize().y / 2.0f;

			// ���� �İ����ٴ��� �ؼ�.. ���̰� �ȸ´´ٸ�?
			if (fLen < fSize)
			{
				// ����� y��ġ�� ������ ��ŭ ���� �ű��
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