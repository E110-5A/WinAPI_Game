#include "jsPlatform.h"

// component
#include "jsCollider.h"
#include "jsRigidbody.h"

// object
#include "jsCreature.h"
#include "jsGroundCheck.h"

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
		SetType(eColliderLayer::Platform);
		mCollider = AddComponent<Collider>();
		mCollider->SetSize(Size(64.0f, 64.0f));
	}
	void Platform::Tick()
	{
		GameObject::Tick();
	}
	void Platform::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}

	void Platform::OnCollisionEnter(Collider* other)
	{
		GameObject* tempObj = other->GetOwner();
		
		if (eColliderLayer::GroundCheck != tempObj->GetType())
			WallProcess(tempObj);
	}
	void Platform::OnCollisionStay(Collider* other)
	{
		GameObject* tempObj = other->GetOwner();

		if (eColliderLayer::GroundCheck != tempObj->GetType())
			WallProcess(tempObj);
	}
	void Platform::OnCollisionExit(Collider* other)
	{
	}

	// �浹���� ��쿡�� ����
	void Platform::WallProcess(GameObject* other)
	{
		// ��� ������Ʈ�� ���� ��������
		Rigidbody* targetRigidbody = other->GetComponent<Rigidbody>();

		// ��� ������Ʈ�� ���� ��ġ ���ϱ�
		Vector2 targetPos = other->GetPos();
		Vector2 wallPos = GetPos();

		// �� ������Ʈ�� ��ġ�� ���ؼ� ���� ã��
		Vector2 wallLocationDir = wallPos - targetPos;
		if (0 > wallLocationDir.x)
			wallLocationDir = Vector2::Left;
		else
			wallLocationDir = Vector2::Right;
		
		// ��� ������Ʈ�� x���� ����
		Vector2 targetVelocity = targetRigidbody->GetVelocity();
		float dot = math::Dot(targetVelocity, wallLocationDir);

		// ����� ���� ���Ѱ�� velocity�� x������ 0���� �����
		Vector2 targetDir = other->GetDir();
		if (wallLocationDir == targetDir)
		{
			// 0 = �ӵ� - (���� *����)
			targetVelocity -= wallLocationDir * dot;
			targetRigidbody->SetVelocity(targetVelocity);
		}
	}
}