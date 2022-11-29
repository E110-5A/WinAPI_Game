#pragma once
#include "jsGameObject.h"

namespace js
{
	struct ProjectileInfo
	{
		Vector2				dir;		// �Ź�
		float				range;		// �ѹ���
		ePlayerAttackType	type;		// �Ź�
		bool				isActive;	// �Ź�
	};

	class Collider;
	class Player;
	class PlayerProjectile : public GameObject
	{
	public:
		PlayerProjectile();
		PlayerProjectile(Pos pos);
		~PlayerProjectile();

		virtual void Init();
		virtual void Tick() override;
		virtual void Render(HDC _hdc) override;

		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;

		// �ѹ��� ȣ���~!
		void SetOwner(Player* owner);


		bool IsActive() { return mInfo.isActive; }

		void Active(ePlayerAttackType type);
		void InActive() { mInfo.isActive = false; }

	private:
		bool AmIDie()
		{
			// ������ġ + X���� * 700�Ÿ� = ������
			Vector2 curPos = mCollider->GetPos();
			float curDistance = fabs(mStartPos.x - curPos.x);
			if (mInfo.range <= curDistance)
			{
				return true;
			}
			return false;
		}

	private:
		Collider* mCollider;
		GameObject* mOwner;
		ProjectileInfo mInfo;

		Pos mStartPos;
	};
}