#pragma once
#include "jsGameObject.h"

namespace js
{
	struct ProjectileInfo
	{
		Vector2				dir;		// �Ź�
		float				range;		// �ѹ���
		ePlayerAttackType	type;		// �Ź�
		bool				unable;	// �Ź�
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