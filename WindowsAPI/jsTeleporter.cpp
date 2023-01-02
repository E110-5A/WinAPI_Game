#include "jsTeleporter.h"

// manager
#include "jsTime.h"
#include "jsInput.h"
#include "jsGameManager.h"
#include "jsSceneManager.h"
#include "jsCamera.h"

// component & resource & Scene
#include "jsCollider.h"
#include "jsImage.h"
#include "jsScene.h"

// object
#include "jsPlayer.h"
#include "jsBossMonster.h"

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
		SetImage(L"Teleporet", L"..\\Resources\\Image\\EventObject\\teleporter.bmp");

		mEventCollider->SetSize(Size(120.0f, 70.0f));
		mEventCollider->SetOffset(Vector2(60, 30));
	}
	void Teleporter::Tick()
	{
		EventObject::Tick();

		if (true == mCharging)
		{
			// 텔레포터 충전하기
			mChargingDeltaTime += Time::GetDeltaTime();

			if (15 <= mChargingDeltaTime)
			{
				mFullyCharged = true;
				mCharging = false;
				mChargingDeltaTime = 0;
			}
		}

		if (true == mFullyCharged && true == mKillBoss)
			mState = eTeleporterState::FullyCharged;

	}
	void Teleporter::Render(HDC hdc)
	{
		Pos pos = Camera::CalculateObjectPos(GetPos());
		Size scale = GetScale();

		BLENDFUNCTION func = {};
		func.AlphaFormat = AC_SRC_ALPHA;
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.SourceConstantAlpha = 255;


		// 1-그려질 위치, 2-그림 크기(scale), 3-복사 위치(LT), 4-원본사이즈
		switch (mState)
		{
		case eTeleporterState::Default:
		{
			AlphaBlend(hdc,
				int(pos.x),
				int(pos.y),
				int(52.0f)* GetScale().x,
				int(29.0f)* GetScale().y,
				mImage->GetDC(),
				int(0),
				int(0),
				int(52.0f),
				int(29.0f), func);
		}
		break;
		case eTeleporterState::Charging:
		{
			AlphaBlend(hdc,
				int(pos.x),
				int(pos.y),
				int(52.0f)* GetScale().x,
				int(29.0f)* GetScale().y,
				mImage->GetDC(),
				int(52.0f),
				int(0),
				int(52.0f),
				int(29.0f), func);
		}
		break;
		case eTeleporterState::FullyCharged:
		{
			AlphaBlend(hdc,
				int(pos.x),
				int(pos.y),
				int(52.0f)* GetScale().x,
				int(29.0f)* GetScale().y,
				mImage->GetDC(),
				int(102),
				int(0),
				int(52.0f),
				int(29.0f), func);
		}
		break;
		}


		// Collider Render
		if (IsAble())
			EventObject::Render(hdc);		
	}
	void Teleporter::AddTeleporter()
	{
		SetAble(false);
		Scene* scene = SceneManager::GetPlayScene();
		// 씬에 추가
		scene->AddGameObject(this, eColliderLayer::Teleporter);

		// 리셋
		mCharging = false;
		mKillBoss = false;
		mFullyCharged = false;

		mState = eTeleporterState::Default;

		SetAble(true);
	}
	void Teleporter::SpawnBoss()
	{
		if (false == mCharging && false == mFullyCharged)
		{
			BossMonster* boss = GameManager::GetBoss();
			// 게임 매니저에서 현재 씬에 보스를 스폰하도록 한다
			boss->Spawn();
			// 보스몬스터의 위치를 내 위치로 변경한다
			boss->SetPos(GetPos() + Pos(0, -20));
		}

		// mCharging 상태로 변경
		mState = eTeleporterState::Charging;
		mCharging = true;
	}
	void Teleporter::NextStage()
	{
		if (true == mKillBoss && true == mFullyCharged)
		{
			// 씬 매니저의 다음 스테이지로 넘기는 함수 호출
			SceneManager::NextStage();
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