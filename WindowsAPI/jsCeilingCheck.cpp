#include "jsCeilingCheck.h"

// component
#include "jsCollider.h"
#include "jsRigidbody.h"
#include "jsAnimator.h"

// collider
#include "jsCreature.h"

#include "jsPlayer.h"

namespace js
{
	CeilingCheck::CeilingCheck()
		: mOwner(nullptr)
		, mCollider(nullptr)
	{
		SetType(eColliderLayer::CollisionCheck);
	}
	CeilingCheck::~CeilingCheck()
	{
	}
	void CeilingCheck::Tick()
	{
		if (nullptr == mCollider)
			mCollider = GetComponent<Collider>();

		SetPos(mOwner->GetPos());

		GameObject::Tick();
	}
	void CeilingCheck::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void CeilingCheck::OnCollisionEnter(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(mOwner);
		// Climb ���¸� �����ϱ�
		if (nullptr != player && ePlayerState::Climb == player->GetState())
			return;

		// õ�忡 �Ӹ� ������ ����
		CeilingProcess(other);

	}
	void CeilingCheck::OnCollisionStay(Collider* other)
	{
	}
	void CeilingCheck::OnCollisionExit(Collider* other)
	{
	}
	void CeilingCheck::CeilingProcess(Collider* other)
	{
		eColliderLayer objLayer = other->GetOwner()->GetType();
		// õ�忡 �Ӹ��� ������
		if (eColliderLayer::Platform == objLayer)
		{
			// y�ӵ��� 0���� �����
			Vector2 playerVelocity = mOwner->GetComponent<Rigidbody>()->GetVelocity();
			playerVelocity.y = 0;
			mOwner->GetComponent<Rigidbody>()->SetVelocity(playerVelocity);
		}
	}
}