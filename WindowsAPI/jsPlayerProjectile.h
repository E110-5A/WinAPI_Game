#pragma once
#include "jsGameObject.h"

namespace js
{
	struct ProjectileInfo
	{
		Vector2				dir;		// 매번
		float				range;		// 한번만
		ePlayerAttackType	type;		// 매번
		bool				unable;	// 매번
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
		void SetInfo();

		bool IsActive() { return mInfo.unable; }

		void Active(ePlayerAttackType type, int damage);
		void InActive() { mInfo.unable = false; }

	private:
		

	private:
		Collider* mCollider;
		Player* mOwner;
		ProjectileInfo mInfo;

		Pos mStartPos;
	};
}