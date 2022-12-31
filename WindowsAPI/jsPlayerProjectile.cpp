#include "jsPlayerProjectile.h"

// 매니저
#include "jsTime.h"

// 컴포넌트
#include "jsCollider.h"

// 오브젝트
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
		// 오너 설정
		mOwner = owner;
		owner->SetWeapon(this);
		// 충돌체 크기 설정
		mInfo.range = mOwner->GetPlayerInfo()->stat->playerOffence->range;
		Collider* onwerCollider = mOwner->GetComponent<Collider>();
		float colliderSizeY = onwerCollider->GetSize().y;
		mCollider->SetSize(Size(mInfo.range, colliderSizeY));
	}

	void PlayerProjectile::Tick()
	{
		// 활성화 상태가 아니면 종료
		if (!mAble)
			return;

		GameObject::Tick();

		Process();
	}

	void PlayerProjectile::Process()
	{		
		mDeltaTime += Time::GetDeltaTime();

		// 찰나의 시간동안 진행됨
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
			// 몬스터 위치 가져오기
			(*iter)->SelfHit(this, mInfo.damage, mInfo.stagger, mInfo.power);
		}
	}


	void PlayerProjectile::Render(HDC hdc)
	{
		// 활성화 상태가 아니면 종료
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
		// vector에 추가된 몬스터를 순회하며 가장 가까운 적 찾기
		float minLenth = mInfo.range + 1.0f;
		Monster* target = nullptr;

		// 타겟 순회하기
		std::vector<Monster*>::iterator iter = mTarget.begin();
		for (; iter != mTarget.end(); ++iter)
		{
			// 몬스터 위치 가져오기
			float targetPosX = (*iter)->GetPos().x;
			// 내 위치 가져오기
			float startPosX = GetPos().x;

			// 타겟과 나 사이의 거리
			float lenth = fabs(targetPosX - startPosX);
			
			// 최소거리인 경우 타겟 갱신
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
		// 타겟 찾기
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

	// 외부에서 호출됨
	void PlayerProjectile::Active(eProjectileType type, float damage, eStagger stagger, float power)
	{
		// 투사체 활성화
		mAble = true;

		// 투사체 기본 정보 갱신
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