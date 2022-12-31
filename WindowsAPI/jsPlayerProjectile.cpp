#include "jsPlayerProjectile.h"

// �Ŵ���
#include "jsTime.h"

// ������Ʈ
#include "jsCollider.h"

// ������Ʈ
#include "jsPlayer.h"
#include "jsObject.h"
#include "jsMonster.h"

namespace js
{
	PlayerProjectile::PlayerProjectile()
		: mOwner (nullptr)
		, mInfo { }
		, mDeltaTime (0.0f)
		, mLifeTime (0.05f)
	{
		SetType(eColliderLayer::Player_Projectile);
		mCollider = AddComponent<Collider>();
		mAble = false;
	}
	PlayerProjectile::PlayerProjectile(Pos pos)
		: mOwner(nullptr)
		, mInfo{ }
		, mDeltaTime(0.0f)
		, mLifeTime(0.05f)
	{
		SetType(eColliderLayer::Player_Projectile);
		mCollider = AddComponent<Collider>();
		mAble = false;
	}
	PlayerProjectile::~PlayerProjectile()
	{
	}

	void PlayerProjectile::SetPlayerInfo(Player* owner)
	{
		// ���� ����
		mOwner = owner;
		owner->SetWeapon(this);
		// �浹ü ũ�� ����
		mInfo.range = mOwner->GetPlayerInfo()->stat->playerOffence->range;
		Collider* onwerCollider = mOwner->GetComponent<Collider>();
		float colliderSizeY = onwerCollider->GetSize().y;
		mCollider->SetSize(Size(mInfo.range, colliderSizeY));
	}

	void PlayerProjectile::Tick()
	{
		// Ȱ��ȭ ���°� �ƴϸ� ����
		if (!mAble)
			return;

		GameObject::Tick();

		Process();
	}

	void PlayerProjectile::Process()
	{		
		mDeltaTime += Time::GetDeltaTime();

		// ������ �ð����� �����
		if (mDeltaTime >= mLifeTime)
		{
			if (eProjectileType::FMJ == mInfo.type)
				FMJ();
			else
				FindTarget();

			InActive();
		}
	}

	void PlayerProjectile::FMJ()
	{
		std::vector<Monster*>::iterator iter = mTarget.begin();
		for (; iter != mTarget.end(); ++iter)
		{
			// ���� ��ġ ��������
			(*iter)->SelfHit(this, mInfo.damage, mInfo.stagger, mInfo.power);
		}
	}


	void PlayerProjectile::Render(HDC hdc)
	{
		// Ȱ��ȭ ���°� �ƴϸ� ����
		if (!mAble)
			return;
		GameObject::Render(hdc);
	}

	void PlayerProjectile::AddTarget(Monster* target)
	{
		mTarget.push_back(target);
	}
	void PlayerProjectile::FindTarget()
	{
		// vector�� �߰��� ���͸� ��ȸ�ϸ� ���� ����� �� ã��
		float minLenth = mInfo.range + 1.0f;
		Monster* target = nullptr;

		// Ÿ�� ��ȸ�ϱ�
		std::vector<Monster*>::iterator iter = mTarget.begin();
		for (; iter != mTarget.end(); ++iter)
		{
			// ���� ��ġ ��������
			float targetPosX = (*iter)->GetPos().x;
			// �� ��ġ ��������
			float startPosX = GetPos().x;

			// Ÿ�ٰ� �� ������ �Ÿ�
			float lenth = fabs(targetPosX - startPosX);
			
			// �ּҰŸ��� ��� Ÿ�� ����
			if (minLenth > lenth)
			{
				minLenth = lenth;
				target = (*iter);
			}
		}
		if (nullptr != target)
			target->SelfHit(this, mInfo.damage, mInfo.stagger, mInfo.power);
	}

	void PlayerProjectile::OnCollisionEnter(Collider* other)
	{
		// Ÿ�� ã��
		GameObject* attacker = other->GetOwner();
		if (eColliderLayer::Monster == attacker->GetType())
		{
			Monster* target = dynamic_cast<Monster*>(attacker);
			if (nullptr != target)
				AddTarget(target);
		}
	}
	void PlayerProjectile::OnCollisionStay(Collider* other)
	{
	}
	void PlayerProjectile::OnCollisionExit(Collider* other)
	{
	}

	// �ܺο��� ȣ���
	void PlayerProjectile::Active(eProjectileType type, float damage, eStagger stagger, float power)
	{
		// ����ü Ȱ��ȭ
		mAble = true;

		// ����ü �⺻ ���� ����
		mInfo.type = type;
		mInfo.damage = damage;
		mInfo.stagger = stagger;
		mInfo.power = power;

		SetDir(mOwner->GetDir());
		SetPos(mOwner->GetPos());
		if (GetDir().x < 0)
		{
			mCollider->SetOffset(Vector2(-mInfo.range / 2, 0));
		}
		else
		{			
			mCollider->SetOffset(Vector2(mInfo.range / 2 - PLAYER_SIZE_X, 0));
		}
	}
}