#pragma once
#include "jsGameObject.h"

namespace js
{
	struct ProjectileInfo
	{
		Vector2				dir;		// 매번
		float				range;		// 한번만
		ePlayerSkillType	type;		// 매번
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

		// SkillInfo를 인자로 받아서 스킬에서 필요하는 기능을 각각 구현해주면 될거같음
		// 아 ㄴㄴ 이건 플레이어에서 알아서 해결해야하는 부분
		void Active(ePlayerSkillType type, int damage);
		void InActive() { mInfo.unable = false; }

	private:
		

	private:
		Collider* mCollider;
		Player* mOwner;
		ProjectileInfo mInfo;

		Pos mStartPos;
	};
}