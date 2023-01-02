#include "jsTeleporter.h"

// manager
#include "jsTime.h"
#include "jsInput.h"

// component
#include "jsCollider.h"

// object
#include "jsPlayer.h"

namespace js
{
	Teleporter::Teleporter()
	{
		Initialize();
	}
	Teleporter::Teleporter(Pos pos)
	{
		SetPos(pos);
		Initialize();
	}
	Teleporter::~Teleporter()
	{
	}

	void Teleporter::Initialize()
	{
		EventObject::Initialize();
		SetImage(L"ChestSprite", L"..\\Resources\\Image\\EventObject\\Chests.bmp");

		mEventCollider->SetSize(Size(52.0f, 29.0f));
	}
	void Teleporter::Tick()
	{
		//
		if (true == mCharging)
		{
			// 텔레포터 충전하기
			mChargingDeltaTime += Time::GetDeltaTime();

			if (30 <= mChargingDeltaTime)
			{
				mFullyCharged = true;
				mCharging = false;
				mChargingDeltaTime = 0;
			}
		}

	}
	void Teleporter::Render(HDC hdc)
	{
		// 텔포 키기전

		// 텔포 킨 후
		
		// 클리어한 경우
	}
	void Teleporter::InitComponent()
	{
		// 충돌체 세팅

	}
	void Teleporter::AddTeleporter()
	{
		// 리셋
		mCharging = false;
		mKillBoss = false;
		mFullyCharged = false;

	}
	void Teleporter::SpawnBoss()
	{
		if (false == mCharging && false == mFullyCharged)
		{
			// 게임 매니저에서 현재 씬에 보스를 스폰하도록 한다

			// 보스몬스터의 위치를 내 위치로 변경한다

		}

		// mCharging 상태로 변경
		mCharging = true;
	}
	void Teleporter::NextStage()
	{
		if (true == mKillBoss && true == mFullyCharged)
		{
			// 씬 매니저의 다음 스테이지로 넘기는 함수 호출
		}
	}
	void Teleporter::OnCollisionEnter(Collider* other)
	{
	}
	void Teleporter::OnCollisionStay(Collider* other)
	{
		Player* player = dynamic_cast<Player*>(other->GetOwner());
		if (KEY_DOWN(eKeyCode::A))
		{
			// 텔레포터와 처음 상호작용할 때 (텔레포터를 켜본적 없고, 충전이 완료되지도 않음)
			if (false == mFullyCharged && false == mCharging)
				SpawnBoss();
			// 충전이 완료되고, 보스를 죽였다면
			if (true == mFullyCharged && true == mKillBoss)
				NextStage();
		}
	}
	void Teleporter::OnCollisionExit(Collider* other)
	{
	}
}