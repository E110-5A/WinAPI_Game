#pragma once
#include "jsGameObject.h"

namespace js
{
	class Collider;
	class Player;
	class Monster;
	class PlayerProjectile : public GameObject
	{
	public:
		PlayerProjectile();
		PlayerProjectile(Pos pos);
		~PlayerProjectile();

		// 씬에서 플레이어가 호출
		void SetPlayerInfo(Player* owner);

		virtual void Tick() override;
		void Process();

		virtual void Render(HDC hdc) override;
		
		// CollisionEnter 에서 호출
		void AddTarget(Creature* target);
		
		// 종료 시점에 호출
		void FindTarget();
		void FMJ();

		// 타격 대상의 함수 호출
		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;

		// 외부에서 호출됨
		void Active(eProjectileType type, float damage, eStagger stagger, float power);
		void InActive() 
		{ 
			mTarget.clear();
			mDeltaTime = 0.0f;
			mAble = false;
		}
		bool IsActive() { return mAble; }

	private:
		Collider*				mCollider;
		Player*					mOwner;

	private:
		ProjectileInfo			mInfo;
		std::vector<Creature*>	mTarget;

		float					mDeltaTime;
		float					mLifeTime;
	};
}