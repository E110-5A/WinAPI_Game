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
			// �ڷ����� �����ϱ�
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


		// 1-�׷��� ��ġ, 2-�׸� ũ��(scale), 3-���� ��ġ(LT), 4-����������
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
		// ���� �߰�
		scene->AddGameObject(this, eColliderLayer::Teleporter);

		// ����
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
			// ���� �Ŵ������� ���� ���� ������ �����ϵ��� �Ѵ�
			boss->Spawn();
			// ���������� ��ġ�� �� ��ġ�� �����Ѵ�
			boss->SetPos(GetPos() + Pos(0, -20));
		}

		// mCharging ���·� ����
		mState = eTeleporterState::Charging;
		mCharging = true;
	}
	void Teleporter::NextStage()
	{
		if (true == mKillBoss && true == mFullyCharged)
		{
			// �� �Ŵ����� ���� ���������� �ѱ�� �Լ� ȣ��
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
			// �ڷ����Ϳ� ó�� ��ȣ�ۿ��� �� (�ڷ����͸� �Ѻ��� ����, ������ �Ϸ������ ����)
			if (false == mFullyCharged && false == mCharging)
				SpawnBoss();
			// ������ �Ϸ�ǰ�, ������ �׿��ٸ�
			if (true == mFullyCharged && true == mKillBoss)
				NextStage();
		}
	}
	void Teleporter::OnCollisionExit(Collider* other)
	{
	}
}