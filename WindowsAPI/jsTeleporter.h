#pragma once
#include "jsEventObject.h"

namespace js
{
	enum class eTeleporterState
	{
		Default,
		Charging,
		FullyCharged,
	};

	class Teleporter : public EventObject
	{
	public:
		Teleporter();
		Teleporter(Pos pos);
		~Teleporter();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;


		void AddTeleporter();


		
		void SpawnBoss();
		void BossKilled() { mKillBoss = true; }

		// Ŭ���� �� ���� ��������
		void NextStage();

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;
	private:
		eTeleporterState mState;
		bool mCharging;
		bool mFullyCharged;
		
		bool mKillBoss;	// ������ óġ�� ���

		float mChargingDeltaTime;
	};
}


