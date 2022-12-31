#include "jsMonster.h"

// �Ŵ���
#include "jsApplication.h"
#include "jsCamera.h"
#include "jsGameManager.h"
#include "jsInput.h"
#include "jsTime.h"

// ���ҽ�
#include "jsResources.h"
#include "jsImage.h"

// ������Ʈ
#include "jsCollider.h"
#include "jsAnimator.h"
#include "jsRigidbody.h"

// ������Ʈ
#include "jsPlayerProjectile.h"
#include "jsPlatform.h"
#include "jsPlayer.h"
#include "jsMonsterAttack.h"

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
		delete mSkillInfo;
	}

	void Monster::Initialize()
	{
		// �⺻ ����
		Creature::Initialize();
		SetScale(Vector2::One * 2);
		SetAnimator();

		// ���ݱ�� ����
		mSkillInfo = new MonsterSkillInfo();
		mDamageObj = new MonsterAttack(this);
		mTarget = GameManager::GetPlayer();

		
		// ������
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


		/*mAnimator->GetEndEvents(L"ImpMoveR") = std::bind(&Monster::ReturnIdle, this);
		mAnimator->GetEndEvents(L"ImpMoveR") = std::bind(&Monster::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"ImpAttackR") = std::bind(&Monster::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"ImpAttackR") = std::bind(&Monster::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"ParentMoveR") = std::bind(&Monster::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"ParentMoveR") = std::bind(&Monster::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"ParentAttackR") = std::bind(&Monster::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"ParentAttackR") = std::bind(&Monster::ReturnIdle, this);*/
	}

	void Monster::ReturnIdle()
	{
		Vector2 dir = GetDir();
		if (dir == Vector2::Right)
			mAnimator->Play(L"ImpIdleR");
		else
			mAnimator->Play(L"ImpIdleL");
	}

	void Monster::InitImp()
	{
		// �浹ü
		SetMonsterStat(310.0f, 0, 0, 13, 1, 100, 16.0f);

		// collider
		mBodyCollider->SetSize(Size(20.f, 25.f) * GetScale());
		mBodyCollider->SetOffset(Vector2(9.f, 14.f));

		mFootCollider->SetSize(Size(15, 5) * GetScale());
		mFootCollider->SetOffset(Vector2(8, 42.f));

		mHeadCollider->SetSize(Size(15, 5) * GetScale());
		mHeadCollider->SetOffset(Vector2(8, -10.f));
		mAnimator->Play(L"ImpTeleportR", false);

		// skill
		InitSkill(mOffenceStat->damage, 0.6f, 2.0f);
		mDropExp = 2;
	}

	void Monster::InitParent()
	{
		// �浹ü
		SetMonsterStat(315.0f, 0, 0, 15, 1, 100, 15.0f);
		
		// collider
		mBodyCollider->SetSize(Size(20.f, 25.f) * GetScale());
		mBodyCollider->SetOffset(Vector2(8.f, 13.f));

		mFootCollider->SetSize(Size(15, 5) * GetScale());
		mFootCollider->SetOffset(Vector2(8, 38.f));

		mHeadCollider->SetSize(Size(15, 5) * GetScale());
		mHeadCollider->SetOffset(Vector2(8, 18.f));

		mAnimator->Play(L"ImpTeleportR", false);

		// skill
		InitSkill(mOffenceStat->damage, 0.6f, 2.0f);
		mDropExp = 3;
	}

	void Monster::InitSkill(float damage, float castDelay, float coolDown)
	{
		mSkillInfo->damage = damage;
		mSkillInfo->castDelay = castDelay;
		mSkillInfo->castDelayTime = 0.0f;
		mSkillInfo->coolDown = coolDown;
		mSkillInfo->coolDownTime = 0.0f;
		mSkillInfo->maxCount = 1;
		mSkillInfo->curCount = 0;
		mSkillInfo->active = false;
		mSkillInfo->run = false;
		mSkillInfo->finish = false;
	}

	void Monster::Spawn(Platform* spawnPlatform)
	{
		// Ȱ��ȭ
		SetAble(true);

		srand((unsigned int)time(NULL));
		// ���� ��ġ ���ϱ� // Platform Pos , Size �� �޾ƿͼ� ���� ������
		Vector2 spawnLT = spawnPlatform->GetPos();
		float spawnWidth = spawnPlatform->GetComponent<Collider>()->GetSize().x;
		float spawnPosX = (rand() % (int)spawnWidth);
		float monsterHight = mBodyCollider->GetSize().y;
		float monsterWidth = mBodyCollider->GetSize().x;

		// ���� ��ġ ����
		SetPos(Vector2(spawnPosX + monsterWidth, spawnLT.y - monsterHight));

		// ���� Ÿ�� ����
		/*int spawnType = (rand() % (int)eMonsterType::End);
		mMonsterType = (eMonsterType)spawnType;*/

		// ������
		mMonsterType = eMonsterType::Imp;
		// ���� �ʱ�ȭ
		switch (mMonsterType)
		{
		case eMonsterType::Imp:
		{
			InitImp();
			mEyesight = mOffenceStat->range * 3;
			mAnimator->Play(L"ImpIdleR");
		}
		break;
		case eMonsterType::Parent:
		{
			InitParent();
			mEyesight = mBodyCollider->GetSize().x * 6;
			mAnimator->Play(L"ParentIdleR");
		}
		break;
		}
		mState = eMonsterState::Stay;
	}


	void Monster::Tick()
	{
		if (false == IsAble())
			return;

		Creature::Tick();
		Cooldown();
		SkillProcess();
		DeadCheck();
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
			Attack();
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
		
		Creature::Render(hdc);

		HBRUSH tr = Application::GetInstance().GetBrush(eBrushColor::Transparent);
		Brush brush(hdc, tr);
		Vector2 pos = GetPos();
		Vector2 size = mBodyCollider->GetSize();

		Rectangle(hdc, pos.x - mEyesight / 2, pos.y, pos.x + mEyesight / 2, pos.y + size.y);

	}

	void Monster::Stay()
	{
		// ���� �� ������ �Ÿ�
		float targetDistance = fabs((GetPos().x - mTarget->GetPos().x));

		// Chase | mEyesight / 2
		if (targetDistance <= mEyesight / 2)
		{
			mState = eMonsterState::Chase;
		}

		// Attack | mOffenceStat->range
		if (targetDistance <= mOffenceStat->range - 50)
		{
			mState = eMonsterState::Skill;
		}
	}

	void Monster::Chase()
	{
		// ���� �� ������ �Ÿ�
		float targetDistance = (GetPos().x - mTarget->GetPos().x);
		// �̵����� ã��
		if (0 < targetDistance)					// x�� ����� ��� ����ġ�� �� ����
			SetDir(Vector2::Left);
		else
			SetDir(Vector2::Right);

		targetDistance = fabs(targetDistance);
		// �÷��̾� �������� �̵�
		mRigidbody->AddForce(GetDir() * 10 * mUtilityStat->moveSpeed * Time::GetDeltaTime());
		
		// ���º��� ����
		// Attack | mOffenceStat->range
		if (targetDistance <= mOffenceStat->range - 50)
		{
			mState = eMonsterState::Skill;
		}
	}


	void Monster::Attack()
	{
		if (false == mSkillInfo->active)
			mSkillInfo->run = true;

		if (true == mSkillInfo->finish)
		{
			mState = eMonsterState::Stay;
			mSkillInfo->finish = false;
		}
	}

	void Monster::Stun()
	{
		// �ð��� ������ Stay�� ���� ����
	}

	void Monster::Death()
	{
		// ����ġ ���
		int bonusExp = (*GameManager::GetDifficulty()) / 2;
		GameManager::AddExp(mDropExp + bonusExp);

		// ��Ȱ��ȭ
		SetAble(false);
	}

	void Monster::Cooldown()
	{
		if (true == mSkillInfo->active)
		{
			mSkillInfo->coolDownTime += Time::GetDeltaTime();
			if (mSkillInfo->coolDownTime > mSkillInfo->coolDown)
			{
				mSkillInfo->active = false;
				mSkillInfo->coolDownTime = 0.0f;
			}
		}
	}

	void Monster::SkillProcess()
	{
		if (true == mSkillInfo->run)
		{
			mSkillInfo->castDelayTime += Time::GetDeltaTime();

			// ��ų ī��Ʈ�� ��ȿ�ϴٸ� �ݺ�
			if (mSkillInfo->curCount < mSkillInfo->maxCount)
			{
				// ���� �غ� �Ǹ� �߻�
				if (mSkillInfo->castDelayTime >= mSkillInfo->castDelay)
				{
					Skill();
					mSkillInfo->castDelayTime = 0.0f;
					++mSkillInfo->curCount;
				}
			}
			else
			{
				mSkillInfo->curCount = 0;
				mSkillInfo->run = false;
				mSkillInfo->finish = true;
			}
		}
	}

	void Monster::Skill()
	{
		mDamageObj->Active();
		mSkillInfo->active = true;
		mSkillInfo->run = true;
	}

	void Monster::DeadCheck()
	{
		if (0 >= mHealthStat->curHP)
		{
			mState = eMonsterState::Death;
		}
	}
	
	void Monster::OnCollisionEnter(Collider* other)
	{
		GameObject* collisionObj = other->GetOwner();
		eColliderLayer type = collisionObj->GetType();

		// ���� ����
		if (type == eColliderLayer::Platform)
		{
			// ���ư��� ���ϰ� ����
			BodyCollision(this);
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
		// ���� ����ؼ� �� ���
		float finalDamage = damage - mHealthStat->defance;

		// �ּ� ���ط�
		if (1 > damage - mHealthStat->defance)
			finalDamage = 1;
		
		mHealthStat->curHP -= finalDamage;
	}

	//stagger, power
	void Monster::SelfKnockBack(float dir, eStagger stagger, float power)
	{
		// ���׷��� ����º��� ���� ���
		if (stagger >= mResistance)		// ������ 0�̰� ���׷��� 0�̸� �˹�
		{
			// �˹�
			Vector2 knockBack = mRigidbody->GetVelocity();
			knockBack.x = dir * power * 2.5f;
			mRigidbody->SetVelocity(knockBack);

			// ������� �ظ� ����
			if (eStagger::Heave == stagger)
				SelfStun(power);
		}
	}

	// power
	void Monster::SelfStun(float power)
	{
		// power�� ���� �����ð��� �޶���
	}
}