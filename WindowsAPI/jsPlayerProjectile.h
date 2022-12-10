#pragma once
#include "jsGameObject.h"

namespace js
{
	struct ProjectileInfo
	{
		eProjectileType		type;		// ����ü ���� (��ų + ������)
		float				range;		// ����ü ��Ÿ�
		bool				unable;		// ����ü Ȱ��ȭ On Off ����
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

		// ������ ���� ����
		void SetOwner(Player* owner);
		// ���� ������ �޾Ƽ� ����
		void SetInfo();


		void Active(eProjectileType type, int damage);
		void InActive() { mInfo.unable = false; }

		bool IsActive() { return mInfo.unable; }

		// Ÿ�� ����� �Լ� ȣ��
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