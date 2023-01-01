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

		// ������ �÷��̾ ȣ��
		void SetPlayerInfo(Player* owner);

		virtual void Tick() override;
		void Process();

		virtual void Render(HDC hdc) override;
		
		// CollisionEnter ���� ȣ��
		void AddTarget(Creature* target);
		
		// ���� ������ ȣ��
		void FindTarget();
		void FMJ();

		// Ÿ�� ����� �Լ� ȣ��
		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;

		// �ܺο��� ȣ���
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