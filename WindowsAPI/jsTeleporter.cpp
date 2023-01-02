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
			// �ڷ����� �����ϱ�
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
		// ���� Ű����

		// ���� Ų ��
		
		// Ŭ������ ���
	}
	void Teleporter::InitComponent()
	{
		// �浹ü ����

	}
	void Teleporter::AddTeleporter()
	{
		// ����
		mCharging = false;
		mKillBoss = false;
		mFullyCharged = false;

	}
	void Teleporter::SpawnBoss()
	{
		if (false == mCharging && false == mFullyCharged)
		{
			// ���� �Ŵ������� ���� ���� ������ �����ϵ��� �Ѵ�

			// ���������� ��ġ�� �� ��ġ�� �����Ѵ�

		}

		// mCharging ���·� ����
		mCharging = true;
	}
	void Teleporter::NextStage()
	{
		if (true == mKillBoss && true == mFullyCharged)
		{
			// �� �Ŵ����� ���� ���������� �ѱ�� �Լ� ȣ��
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