#pragma once
#include "jsGameObject.h"

namespace js
{
	struct ProjectileInfo
	{
		Vector2				dir;		// 매번
		float				range;		// 한번만
		ePlayerAttackType	type;		// 매번
		bool				isActive;	// 매번
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

		// 한번만 호출됨~!
		void SetOwner(Player* owner);


		bool IsActive() { return mInfo.isActive; }

		void Active(ePlayerAttackType type);
		void InActive() { mInfo.isActive = false; }

	private:
		bool AmIDie()
		{
			// 시작위치 + X방향 * 700거리 = 목적지
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