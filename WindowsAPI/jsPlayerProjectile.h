#pragma once
#include "jsGameObject.h"

namespace js
{
	class Collider;
	class Player;
	class PlayerProjectile : public GameObject
	{
	public:
		PlayerProjectile();
		PlayerProjectile(Pos pos);
		~PlayerProjectile();

		virtual void Initialize() override;
		void InitComponent();
		virtual void Tick() override;
		void Process();
		void Shutdown();


		virtual void Render(HDC _hdc) override;

		// 씬에서 오너 세팅
		void SetOwner(Player* owner);
		// 오너 정보를 받아서 세팅
		void SetInfo();


		void Active(eProjectileType type, float damage, eStagger stagger, float power);
		void InActive() { mInfo.unable = false; }

		bool IsActive() { return mInfo.unable; }

		void BlowHit(Monster* target);

		// 타격 대상의 함수 호출
		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;


	private:
		Collider* mCollider;
		Player* mOwner;
		ProjectileInfo mInfo;
		Pos mStartPos;
		PlayerStat* mPlayerStat;
	};
}