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
		void FMJ();

		virtual void Render(HDC _hdc) override;
		
		// CollisionEnter ���� ȣ��
		void AddTarget(Monster* target);
		// ���� ������ ȣ��
		void FindTarget();



		bool IsActive() { return mInfo.active; }
		// Ÿ�� ����� �Լ� ȣ��
		virtual void OnCollisionEnter(Collider* other)override;
		virtual void OnCollisionStay(Collider* other)override;
		virtual void OnCollisionExit(Collider* other)override;

		// �ܺο��� ȣ���
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