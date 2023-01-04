#include "jsBossMonster.h"
#include "jsApplication.h"

#include "jsResources.h"
#include "jsScene.h"
// manager
#include "jsSceneManager.h"
#include "jsGameManager.h"
#include "jsTime.h"
// component
#include "jsAnimator.h"
#include "jsCollider.h"

// object
#include "jsMonsterAttack.h"
#include "jsPlayer.h"
#include "jsTeleporter.h"

namespace js
{
	BossMonster::BossMonster()
	{
		Initialize();
	}
	BossMonster::BossMonster(Pos pos)
	{
		Initialize();
		SetPos(pos);
	}
	BossMonster::~BossMonster()
	{
		delete mAttack1;
		delete mAttack2;
	}
	void BossMonster::Initialize()
	{
		Creature::Initialize();
		SetImage(Resources::Load<Image>(L"Boss", L"..\\Resources\\Image\\Enemy\\boss.bmp"));
		SetAnimator();
		mResistance = eStagger::Heave;
		
		// 공격기능 세팅
		mAttack1 = new MonsterSkillInfo();
		mAttack2 = new MonsterSkillInfo();
		mDamageObj = new MonsterAttack(this);
		mTarget = GameManager::GetPlayer();

		SetAble(false);
	}
	void BossMonster::SetAnimator()
	{
		// Imp Aniamtion
		mAnimator->CreateAnimation(L"ColossusIdleR", mSpriteImage, Pos(0.f, 0.f), Size(86.f, 119.f)
			, Vector2(0.f, 0.f), 1, 0.1f);
		mAnimator->CreateAnimation(L"ColossusIdleL", mSpriteImage, Pos(86.f, 0.f), Size(86.f, 119.f)
			, Vector2(0.f, 0.f), 1, 0.1f);

		mAnimator->CreateAnimation(L"ColossusMoveR", mSpriteImage, Pos(0.f, 119.f), Size(86.f, 119.f)
			, Vector2(0.f, 0.f), 10, 0.15f);
		mAnimator->CreateAnimation(L"ColossusMoveL", mSpriteImage, Pos(0.f, 238.f), Size(86.f, 119.f)
			, Vector2(0.f, 0.f), 10, 0.15f);

		mAnimator->CreateAnimation(L"ColossusAttack1R", mSpriteImage, Pos(0.f, 357.f), Size(106.f, 119.f)
			, Vector2(0.f, 0.f), 9, 0.15f);
		mAnimator->CreateAnimation(L"ColossusAttack1L", mSpriteImage, Pos(0.f, 476.f), Size(106.f, 119.f)
			, Vector2(0.f, 0.f), 9, 0.15f);

		mAnimator->CreateAnimation(L"ColossusAttack2R", mSpriteImage, Pos(0.f, 595.f), Size(174.f, 119.f)
			, Vector2(0.f, 0.f), 15, 0.15f);
		mAnimator->CreateAnimation(L"ColossusAttack2L", mSpriteImage, Pos(0.f, 714.f), Size(174.f, 119.f)
			, Vector2(0.f, 0.f), 15, 0.15f);

		mAnimator->CreateAnimation(L"ColossusDeathR", mSpriteImage, Pos(0.f, 833.f), Size(140.0f, 141.f)
			, Vector2(0.f, 0.f), 15, 0.15f);
		mAnimator->CreateAnimation(L"ColossusDeathL", mSpriteImage, Pos(0.f, 974.f), Size(140.0f, 141.f)
			, Vector2(0.f, 0.f), 15, 0.15f);
	}

	void BossMonster::InitColossus()
	{
		SetMonsterStat(400.f, 0, 0, 40, 1, 200, 13.f);
		
		mBodyCollider->SetSize(Size(86.f, 119.f));
		mFootCollider->SetSize(Size(86.f, 40.f));
		mFootCollider->SetOffset(Vector2(0, 60.f));


		mAnimator->Play(L"ColossusIdleR");

		InitSkill(mAttack1, mOffenceStat->damage, 0.6f, 2.0f);
		InitSkill(mAttack2, mOffenceStat->damage, 0.6f, 2.0f);

		mDropExp = 20;
	}
	

	void BossMonster::InitSkill(MonsterSkillInfo* skill, float damage, float castDelay, float coolDown)
	{
		skill->damage = damage;
		skill->castDelay = castDelay;
		skill->castDelayTime = 0.0f;
		skill->coolDown = coolDown;
		skill->coolDownTime = 0.0f;
		skill->maxCount = 1;
		skill->curCount = 0;
		skill->active = false;
		skill->run = false;
		skill->finish = false;
	}
	void BossMonster::Spawn()
	{
		// 활성화
		SetAble(true);
		
		// 스텟 설정
		mBossType = eBossType::Colossus;
		InitColossus();
		mEyesight = mBodyCollider->GetSize().x * 10;

		// 상태 초기화
		mState = eBossState::Stay;

		// 씬에서 보스 UI 활성화
		mPlayScene->PushBossUI();
	}
	void BossMonster::Tick()
	{
		if (false == IsAble())
			return;

		Creature::Tick();
		Cooldown();
		SkillProcess();
		DeadCheck();
		switch (mState)
		{
		case eBossState::Stay:
		{
			Stay();
		}
		break;
		case eBossState::Chase:
		{
			Chase();
		}
		break;
		case eBossState::Attack1:
		{
			Attack1();
		}
		break;
		case eBossState::Attack2:
		{
			Attack2();
		}
		break;
		case eBossState::Death:
		{
			Death();
		}
		break;
		}
	}
	void BossMonster::Render(HDC hdc)
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

	void BossMonster::Stay()
	{
		// 대상과 나 사이의 거리
		float targetDistance = fabs((GetPos().x - mTarget->GetPos().x));

		// Chase | mEyesight / 2
		if (targetDistance <= mEyesight / 2)
		{
			mState = eBossState::Chase;
			if (Vector2::Right == GetDir())
				mAnimator->Play(L"ColossusMoveR");
			else
				mAnimator->Play(L"ColossusMoveL");
		}

		// Attack | mOffenceStat->range
		if (targetDistance <= mOffenceStat->range - 50)
		{
			srand((unsigned int)time(NULL));
			float skills = (rand() % 2);
			if (0 == skills)
			{
				if (Vector2::Right == GetDir())
					mAnimator->Play(L"ColossusAttack1R");
				else
					mAnimator->Play(L"ColossusAttack1L");
				mState = eBossState::Attack1;
			}
			else
			{
				if (Vector2::Right == GetDir())
					mAnimator->Play(L"ColossusAttack2R");
				else
					mAnimator->Play(L"ColossusAttack2L");
				mState = eBossState::Attack2;
			}
		}
	}
	void BossMonster::Chase()
	{
		// 대상과 나 사이의 거리
		float targetDistance = (GetPos().x - mTarget->GetPos().x);
		// 이동방향 찾기
		if (0 < targetDistance)					// x가 양수일 경우 벽위치는 내 왼쪽
			SetDir(Vector2::Left);
		else
			SetDir(Vector2::Right);

		targetDistance = fabs(targetDistance);
		// 플레이어 방향으로 이동
		mRigidbody->AddForce(GetDir() * 5.f * mUtilityStat->moveSpeed * Time::GetDeltaTime());
		if (targetDistance <= mOffenceStat->range - 50)
		{
			srand((unsigned int)time(NULL));
			float skills = (rand() % 2);
			if (0 == skills)
			{
				if (Vector2::Right == GetDir())
					mAnimator->Play(L"ColossusAttack1R");
				else
					mAnimator->Play(L"ColossusAttack1L");
				mState = eBossState::Attack1;
			}
			else
			{
				if (Vector2::Right == GetDir())
					mAnimator->Play(L"ColossusAttack2R");
				else
					mAnimator->Play(L"ColossusAttack2L");
				mState = eBossState::Attack2;
			}
		}
	}
	void BossMonster::Attack1()
	{
		if (false == mAttack1->active)
			mAttack1->run = true;

		if (true == mAttack1->finish)
		{
			mState = eBossState::Stay;
			mAttack1->finish = false;

			if (Vector2::Right == GetDir())
				mAnimator->Play(L"ColossusIdleR");
			else
				mAnimator->Play(L"ColossusIdleL");
		}
	}
	void BossMonster::Attack2()
	{
		if (false == mAttack2->active)
			mAttack2->run = true;

		if (true == mAttack2->finish)
		{
			mState = eBossState::Stay;
			mAttack2->finish = false;

			if (Vector2::Right == GetDir())
				mAnimator->Play(L"ColossusIdleR");
			else
				mAnimator->Play(L"ColossusIdleL");
		}
	}
	void BossMonster::Death()
	{
		// ..?
		GameManager::AddExp(20);
		Teleporter* tp = GameManager::GetTeleporter();
		tp->BossKilled();
		SetAble(false);
	}
	void BossMonster::Cooldown()
	{
		if (true == mAttack1->active)
		{
			mAttack1->coolDownTime += Time::GetDeltaTime();
			if (mAttack1->coolDownTime > mAttack1->coolDown)
			{
				mAttack1->active = false;
				mAttack1->coolDownTime = 0.0f;
			}
		}
		if (true == mAttack2->active)
		{
			mAttack2->coolDownTime += Time::GetDeltaTime();
			if (mAttack2->coolDownTime > mAttack2->coolDown)
			{
				mAttack2->active = false;
				mAttack2->coolDownTime = 0.0f;
			}
		}
	}
	void BossMonster::SkillProcess()
	{
		if (true == mAttack1->run)
		{
			// 딜레이 계산
			mAttack1->castDelayTime += Time::GetDeltaTime();

			// 스킬 카운트가 유효하다면 반복
			if (mAttack1->curCount < mAttack1->maxCount)
			{
				// 시전 준비가 되면 발사
				if (mAttack1->castDelayTime >= mAttack1->castDelay)
				{
					Skill(eBossAttackType::A);
					mAttack1->castDelayTime = 0.0f;
					++mAttack1->curCount;
				}
			}
			else
			{
				mAttack1->curCount = 0;
				mAttack1->run = false;
				mAttack1->finish = true;
			}
		}
		if (true == mAttack2->run)
		{
			// 딜레이 계산
			mAttack2->castDelayTime += Time::GetDeltaTime();

			// 스킬 카운트가 유효하다면 반복
			if (mAttack2->curCount < mAttack2->maxCount)
			{
				// 시전 준비가 되면 발사
				if (mAttack2->castDelayTime >= mAttack2->castDelay)
				{
					Skill(eBossAttackType::B);
					mAttack2->castDelayTime = 0.0f;
					++mAttack2->curCount;
				}
			}
			else
			{
				mAttack2->curCount = 0;
				mAttack2->run = false;
				mAttack2->finish = true;
			}
		}
	}
	void BossMonster::Skill(eBossAttackType type)
	{
		switch (type)
		{
		case eBossAttackType::A:
		{
			mDamageObj->Active();
			mAttack1->active = true;
			mAttack1->run = true;
		}
		break;
		case eBossAttackType::B:
		{
			mDamageObj->Active();
			mAttack2->active = true;
			mAttack2->run = true;
		}
		break;
		}
		
	}
	void BossMonster::DeadCheck()
	{
		if (0 >= mHealthStat->curHP)
		{
			// 사망!
			GameManager::KillBoss();
			mPlayScene->PopBossUI();
			mState = eBossState::Death;
		}
	}
	void BossMonster::AddBoss()
	{
		SetAble(false);
		Scene* scene = SceneManager::GetPlayScene();
		// 씬에 추가
		scene->AddGameObject(this, eColliderLayer::Monster);
		scene->AddGameObject(mDamageObj, eColliderLayer::Projectile);
	}
	void BossMonster::OnCollisionEnter(Collider* other)
	{
	}
	void BossMonster::OnCollisionStay(Collider* other)
	{
	}
	void BossMonster::OnCollisionExit(Collider* other)
	{
	}
	void BossMonster::SelfHit(GameObject* attaker, float damage, eStagger stagger, float power)
	{
		SelfDamaged(damage);
	}
	void BossMonster::SelfDamaged(float damage)
	{
		// 방어력 계산해서 피 까기
		float finalDamage = damage - mHealthStat->defance;

		// 최소 피해량
		if (1 > damage - mHealthStat->defance)
			finalDamage = 1;

		mHealthStat->curHP -= finalDamage;
	}
}