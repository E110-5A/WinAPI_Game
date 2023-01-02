#pragma once
#include "jsEventObject.h"

namespace js
{
	class Teleporter : public EventObject
	{
	public:
		Teleporter();
		Teleporter(Pos pos);
		~Teleporter();

		virtual void Initialize() override;
		virtual void Tick() override;
		virtual void Render(HDC hdc) override;

		virtual void InitComponent();

		void AddTeleporter();


		
		void SpawnBoss();
		void BossKilled() { mKillBoss = true; }

		// 클리어 후 다음 스테이지
		void NextStage();

		virtual void OnCollisionEnter(Collider* other) override;
		virtual void OnCollisionStay(Collider* other) override;
		virtual void OnCollisionExit(Collider* other) override;
	private:
		bool mCharging;
		bool mFullyCharged;
		
		bool mKillBoss;	// 보스를 처치한 경우

		float mChargingDeltaTime;
	};
}


