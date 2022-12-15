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
		void FMJ();

		virtual void Render(HDC _hdc) override;
		
		// CollisionEnter 에서 호출
		void AddTarget(Monster* target);
		// 종료 시점에 호출
		void FindTarget();



		bool IsActive() { return mInfo.active; }
		// 타격 대상의 함수 호출
		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;

		// 외부에서 호출됨
		void Active(eProjectileType type, float damage, eStagger stagger, float power);
		void InActive() 
		{ 
			mDeltaTime = 0.0f;
			mInfo.active = false; 
		}

	private:
		Collider*				mCollider;
		Player*					mOwner;

	private:
		ProjectileInfo			mInfo;
		std::vector<Monster*>	mTarget;

		float					mDeltaTime;
		float					mLifeTime;
	};
}