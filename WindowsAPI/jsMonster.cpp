#include "jsMonster.h"

// 매니저
#include "jsCamera.h"
#include "jsGameManager.h"

// 리소스
#include "jsResources.h"
#include "jsImage.h"

// 컴포넌트
#include "jsCollider.h"
#include "jsAnimator.h"
#include "jsRigidbody.h"

// 오브젝트
#include "jsPlayerProjectile.h"
#include "jsPlatform.h"

namespace js
{
	Monster::Monster()
	{
		Initialize();
	}
	Monster::Monster(Pos pos)
	{
		Initialize();
		SetPos(pos);
	}
	Monster::~Monster()
	{
	}

	void Monster::Initialize()
	{
		Creature::Initialize();
		mTarget = GameManager::GetPlayer();
		SetAnimator();
		SetAble(false);
	}
	void Monster::SetAnimator()
	{
		// Imp Aniamtion
		mAnimator->CreateAnimation(L"ImpIdleR", mSpriteImage, Pos(0.f, 0.f), Size(17.f, 21.f)
			, Vector2(0.f, 0.f), 1, 0.1f);
		mAnimator->CreateAnimation(L"ImpIdleL", mSpriteImage, Pos(0.f, 21.f), Size(17.f, 21.f)
			, Vector2(0.f, 0.f), 1, 0.1f);

		mAnimator->CreateAnimation(L"ImpMoveR", mSpriteImage, Pos(0.f, 42.f), Size(18.0f, 25.f)
			, Vector2(0.f, 0.f), 6, 0.1f);
		mAnimator->CreateAnimation(L"ImpMoveL", mSpriteImage, Pos(0.f, 67.f), Size(18.0f, 25.f)
			, Vector2(0.f, 0.f), 6, 0.1f);

		mAnimator->CreateAnimation(L"ImpTeleportR", mSpriteImage, Pos(0.f, 92.f), Size(17.f, 21.f)
			, Vector2(0.f, 0.f), 3, 0.1f);
		mAnimator->CreateAnimation(L"ImpTeleportL", mSpriteImage, Pos(0.f, 113.f), Size(17.f, 21.f)
			, Vector2(0.f, 0.f), 3, 0.1f);

		mAnimator->CreateAnimation(L"ImpAttackR", mSpriteImage, Pos(0.f, 134.f), Size(33.f, 21.f)
			, Vector2(-7.f, 0.f), 11, 0.1f);
		mAnimator->CreateAnimation(L"ImpAttackL", mSpriteImage, Pos(0.f, 155.f), Size(33.f, 21.f)
			, Vector2(-10.f, 0.f), 11, 0.1f);

		mAnimator->CreateAnimation(L"ImpDeathR", mSpriteImage, Pos(0.f, 176.f), Size(26.0f, 21.f)
			, Vector2(-5.f, 0.f), 8, 0.1f);
		mAnimator->CreateAnimation(L"ImpDeathL", mSpriteImage, Pos(0.f, 197.f), Size(26.0f, 21.f)
			, Vector2(-5.f, 0.f), 8, 0.1f);


		// Parent Animation
		mAnimator->CreateAnimation(L"ParentSpawn", mSpriteImage, Pos(0.f, 92.f), Size(17.f, 21.f)
			, Vector2(0.f, 0.f), 3, 0.1f);

		mAnimator->CreateAnimation(L"ParentIdleR", mSpriteImage, Pos(0.f, 0.f), Size(17.f, 21.f)
			, Vector2(0.f, 0.f), 1, 0.1f);
		mAnimator->CreateAnimation(L"ParentIdleL", mSpriteImage, Pos(0.f, 21.f), Size(17.f, 21.f)
			, Vector2(0.f, 0.f), 1, 0.1f);

		mAnimator->CreateAnimation(L"ParentMoveR", mSpriteImage, Pos(0.f, 42.f), Size(18.0f, 25.f)
			, Vector2(0.f, 0.f), 6, 0.1f);
		mAnimator->CreateAnimation(L"ParentMoveL", mSpriteImage, Pos(0.f, 67.f), Size(18.0f, 25.f)
			, Vector2(0.f, 0.f), 6, 0.1f);
		mAnimator->CreateAnimation(L"ParentAttackR", mSpriteImage, Pos(0.f, 134.f), Size(33.f, 21.f)
			, Vector2(-7.f, 0.f), 11, 0.1f);
		mAnimator->CreateAnimation(L"ParentAttackL", mSpriteImage, Pos(0.f, 155.f), Size(33.f, 21.f)
			, Vector2(-10.f, 0.f), 11, 0.1f);

		mAnimator->CreateAnimation(L"ParentDeathR", mSpriteImage, Pos(0.f, 176.f), Size(26.0f, 21.f)
			, Vector2(-5.f, 0.f), 8, 0.1f);
		mAnimator->CreateAnimation(L"ParentDeathL", mSpriteImage, Pos(0.f, 197.f), Size(26.0f, 21.f)
			, Vector2(-5.f, 0.f), 8, 0.1f);

		mAnimator->GetCompleteEvents(L"ImpTeleportR") = std::bind(&Monster::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"ParentDeathR") = std::bind(&Monster::ReturnIdle, this);

	}

	void Monster::ImpInit()
	{
		// 충돌체
		SetMonsterStat(310.0f, 0, 0, 13, 1, 600, 16.0f);

		// collider
		mBodyCollider->SetSize(Size(20.f, 25.f) * GetScale());
		mBodyCollider->SetOffset(Vector2(8.f, 13.f));
		
		mFootCollider->SetSize(Size(15, 5) * GetScale());
		mFootCollider->SetOffset(Vector2(8, 38.f));

		mHeadCollider->SetSize(Size(15, 5) * GetScale());
		mHeadCollider->SetOffset(Vector2(8, 18.f));

	}

	void Monster::ParentInit()
	{
		// 충돌체
		SetMonsterStat(315.0f, 0, 0, 15, 1, 600, 15.0f);
		
		// collider
		mBodyCollider->SetSize(Size(20.f, 25.f) * GetScale());
		mBodyCollider->SetOffset(Vector2(8.f, 13.f));

		mFootCollider->SetSize(Size(15, 5) * GetScale());
		mFootCollider->SetOffset(Vector2(8, 38.f));

		mHeadCollider->SetSize(Size(15, 5) * GetScale());
		mHeadCollider->SetOffset(Vector2(8, 18.f));
	}

	void Monster::Spawn(Platform* spawnPlatform)
	{
		srand((unsigned int)time(NULL));
		// 스폰 위치 정하기 // Platform Pos , Size 값 받아와서 랜덤 돌리기
		Vector2 spawnLT = spawnPlatform->GetPos();
		float spawnWidth = spawnPlatform->GetComponent<Collider>()->GetSize().x;
		float spawnPosX = (rand() % (int)spawnWidth);
		float monsterHight = mBodyCollider->GetSize().y;
		float monsterWidth = mBodyCollider->GetSize().x;

		// 스폰 위치 설정
		SetPos(Vector2(spawnPosX + monsterWidth, spawnLT.y - monsterHight));

		// 몬스터 타입 설정
		/*int spawnType = (rand() % (int)eMonsterType::End);
		mMonsterType = (eMonsterType)spawnType;*/

		// 디버깅용
		mMonsterType = eMonsterType::Imp;
		// 몬스터 초기화
		switch (mMonsterType)
		{
		case eMonsterType::Imp:
		{
			ImpInit();
			mEyesight = mBodyCollider->GetSize().x * 6;
			mAnimator->Play(L"ImpTeleportR", false);
		}
		break;
		case eMonsterType::Parent:
		{
			ImpInit();
			mEyesight = mBodyCollider->GetSize().x * 6;
			mAnimator->Play(L"ParentSpawn", false);
		}
		break;
		}

		// 활성화
		mAble = true;
	}

	// Spawn 애니메이션 끝나면 실행될 내용
	void Monster::ReturnIdle()
	{
		// 애니메이션
		switch (mMonsterType)
		{
		case eMonsterType::Imp:
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"ImpIdleR");
			else
				mAnimator->Play(L"ImpIdleL");
		}
		break;
		case eMonsterType::Parent:
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"ParentIdleR");
			else
				mAnimator->Play(L"ParentIdleL");
		}
		break;
		}

		// 상태 변경
		mState = eMonsterState::Stay;
	}


	void Monster::Tick()
	{
		if (false == IsAble())
			return;

		Creature::Tick();

		switch (mState)
		{
		case eMonsterState::Stay:
		{
			Stay();
		}
		break;
		case eMonsterState::Chase:
		{
			Chase();
		}
		break;
		case eMonsterState::Skill:
		{
			Skill();
		}
		break;
		case eMonsterState::Stun:
		{
			Stun();
		}
		break;
		case eMonsterState::Death:
		{
			Death();
		}
		break;
		}
	}

	void Monster::Render(HDC hdc)
	{
		if (false == IsAble())
			return;
		Vector2 pos = GetPos();
		Vector2 size = mBodyCollider->GetSize();
		Rectangle(hdc, pos.x - mEyesight / 2, pos.y, pos.x + mEyesight / 2, pos.y + size.y);
		
		
		
		Creature::Render(hdc);


	}

	void Monster::Stay()
	{
		// 애니메이션
		switch (mMonsterType)
		{
		case eMonsterType::Imp:
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"ImpIdleR");
			else
				mAnimator->Play(L"ImpIdleL");
		}
		break;
		case eMonsterType::Parent:
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"ParentIdleR");
			else
				mAnimator->Play(L"ParentIdleL");
		}
		break;
		}

		// 로직
		 
		// 상태변경 조건
		
		// 플레이어가 인지범위 내에 있으면 Chase
		// 플레이어가 공격범위 내에 있으면 Skill
	}

	void Monster::Chase()
	{
		// 애니메이션
		switch (mMonsterType)
		{
		case eMonsterType::Imp:
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"ImpIdleR");
			else
				mAnimator->Play(L"ImpIdleL");
		}
		break;
		case eMonsterType::Parent:
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"ParentIdleR");
			else
				mAnimator->Play(L"ParentIdleL");
		}
		break;
		}

		// 로직

		// 상태변경 조건
		// 플레이어가 인지범위 밖에 있으면 Stay
		// 플레이어가 공격범위 내에 있으면 Skill
	}

	void Monster::Skill()
	{
		// 애니메이션
		switch (mMonsterType)
		{
		case eMonsterType::Imp:
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"ImpIdleR");
			else
				mAnimator->Play(L"ImpIdleL");
		}
		break;
		case eMonsterType::Parent:
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"ParentIdleR");
			else
				mAnimator->Play(L"ParentIdleL");
		}
		break;
		}

		// 로직

		// 상태변경 조건
		// 공격이 끝나면 Stay
	}

	void Monster::Stun()
	{
		// 애니메이션
		switch (mMonsterType)
		{
		case eMonsterType::Imp:
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"ImpIdleR");
			else
				mAnimator->Play(L"ImpIdleL");
		}
		break;
		case eMonsterType::Parent:
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"ParentIdleR");
			else
				mAnimator->Play(L"ParentIdleL");
		}
		break;
		}

		// 로직

		// 상태변경 조건
		// 초 세기
	}

	void Monster::Death()
	{
		// 애니메이션
		switch (mMonsterType)
		{
		case eMonsterType::Imp:
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"ImpIdleR");
			else
				mAnimator->Play(L"ImpIdleL");
		}
		break;
		case eMonsterType::Parent:
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"ParentIdleR");
			else
				mAnimator->Play(L"ParentIdleL");
		}
		break;
		}

		// 로직

		// 상태변경 조건
		// 비활성화
		// 경험치 드랍
	}
	
	void Monster::OnCollisionEnter(Collider* other)
	{
		GameObject* collisionObj = other->GetOwner();
		eColliderLayer type = collisionObj->GetType();

		// 벽에 닿음
		if (type == eColliderLayer::Platform)
		{
			// 나아가지 못하게 막기
			BodyCollision(collisionObj);
		}
	}
	void Monster::OnCollisionStay(Collider* other)
	{
	}
	void Monster::OnCollisionExit(Collider* other)
	{
	}

	// damage, stagger, power
	void Monster::SelfHit(GameObject* attaker, float damage, eStagger stagger, float power)
	{
		SelfDamaged(damage);
		SelfKnockBack(attaker->GetDir().x, stagger, power);
	}

	// damage
	void Monster::SelfDamaged(float damage)
	{
		// 방어력 계산해서 피 까기
		float finalDamage = damage - mHealthStat->defance;

		// 최소 피해량
		if (1 > damage - mHealthStat->defance)
			finalDamage = 1;
		
		mHealthStat->curHP -= finalDamage;
	}

	//stagger, power
	void Monster::SelfKnockBack(float dir, eStagger stagger, float power)
	{
		// 저항력이 관통력보다 낮은 경우
		if (stagger >= mResistance)		// 관통이 0이고 저항력이 0이면 넉백
		{
			// 넉백
			Vector2 knockBack = mRigidbody->GetVelocity();
			knockBack.x = dir * power * 2.5f;
			mRigidbody->SetVelocity(knockBack);

			// 관통력이 쌔면 기절
			if (eStagger::Heave == stagger)
				SelfStun(power);
		}
	}

	// power
	void Monster::SelfStun(float power)
	{
		// power에 따라서 기절시간이 달라짐
	}
}