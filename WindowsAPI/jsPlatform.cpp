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

	// 충돌중인 경우에만 진입
	void Platform::WallProcess(GameObject* other)
	{
		// 대상 오브젝트의 정보 가져오기
		Rigidbody* targetRigidbody = other->GetComponent<Rigidbody>();

		// 대상 오브젝트와 나의 위치 구하기
		Vector2 targetPos = other->GetPos();
		Vector2 wallPos = GetPos();

		// 두 오브젝트의 위치를 구해서 방향 찾기
		Vector2 wallLocationDir = wallPos - targetPos;
		if (0 > wallLocationDir.x)
			wallLocationDir = Vector2::Left;
		else
			wallLocationDir = Vector2::Right;
		
		// 대상 오브젝트의 x성분 추출
		Vector2 targetVelocity = targetRigidbody->GetVelocity();
		float dot = math::Dot(targetVelocity, wallLocationDir);

		// 대상이 나를 향한경우 velocity의 x성분을 0으로 만들기
		Vector2 targetDir = other->GetDir();
		if (wallLocationDir == targetDir)
		{
			// 0 = 속도 - (방향 *성분)
			targetVelocity -= wallLocationDir * dot;
			targetRigidbody->SetVelocity(targetVelocity);
		}
	}
}