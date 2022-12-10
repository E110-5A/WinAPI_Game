#pragma once
#include "jsGameObject.h"

namespace js
{
	struct ProjectileInfo
	{
		eProjectileType		type;		// 투사체 종류 (스킬 + 아이템)
		float				range;		// 투사체 사거리
		bool				unable;		// 투사체 활성화 On Off 여부
	};

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


		void Active(eProjectileType type, int damage);
		void InActive() { mInfo.unable = false; }

		bool IsActive() { return mInfo.unable; }

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