#include "jsMonster.h"

// �Ŵ���
#include "jsCamera.h"
#include "jsGameManager.h"

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
		// �浹ü
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
		// �浹ü
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

		// Ȱ��ȭ
		mAble = true;
	}

	// Spawn �ִϸ��̼� ������ ����� ����
	void Monster::ReturnIdle()
	{
		// �ִϸ��̼�
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

		// ���� ����
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
		// �ִϸ��̼�
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

		// ����
		 
		// ���º��� ����
		
		// �÷��̾ �������� ���� ������ Chase
		// �÷��̾ ���ݹ��� ���� ������ Skill
	}

	void Monster::Chase()
	{
		// �ִϸ��̼�
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

		// ����

		// ���º��� ����
		// �÷��̾ �������� �ۿ� ������ Stay
		// �÷��̾ ���ݹ��� ���� ������ Skill
	}

	void Monster::Skill()
	{
		// �ִϸ��̼�
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

		// ����

		// ���º��� ����
		// ������ ������ Stay
	}

	void Monster::Stun()
	{
		// �ִϸ��̼�
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

		// ����

		// ���º��� ����
		// �� ����
	}

	void Monster::Death()
	{
		// �ִϸ��̼�
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

		// ����

		// ���º��� ����
		// ��Ȱ��ȭ
		// ����ġ ���
	}
	
	void Monster::OnCollisionEnter(Collider* other)
	{
		GameObject* collisionObj = other->GetOwner();
		eColliderLayer type = collisionObj->GetType();

		// ���� ����
		if (type == eColliderLayer::Platform)
		{
			// ���ư��� ���ϰ� ����
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