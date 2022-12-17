#include "jsPlayer.h"

// 매니저
#include "jsTime.h"
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsCamera.h"
#include "jsPlayerManager.h"

// 리소스
#include "jsImage.h"
#include "jsResources.h"

#include "jsScene.h"

// 콜라이더
#include "jsAnimator.h"
#include "jsCollider.h"
#include "jsRigidbody.h"

// 오브젝트
#include "jsObject.h"
#include "jsPlayerProjectile.h"
#include "jsGroundCheck.h"
#include "jsMonster.h"

namespace js
{
	Player::Player()
		: mWeaponID(0)
		, mBlocked(false)
	{
		SetPos(Pos(400.f, 1000.f));
		Initialize();
	}
	Player::Player(Pos pos)
		: mWeaponID(0)
		, mBlocked(false)
	{
		SetPos(pos);
		Initialize();
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		SetType(eColliderLayer::Player);
		SetName(L"Player");
		// 스텟 연동
		SetPlayerHealth(PlayerManager::GetInstance().GetPlayerStat().playerHealth);
		SetPlayerOffence(PlayerManager::GetInstance().GetPlayerStat().playerOffence);
		SetPlayerUtility(PlayerManager::GetInstance().GetPlayerStat().playerUtility);

		// 애니메이션 스프라이트 로딩
		if (nullptr == mSpriteImage)
			SetImage(Resources::Load<Image>(L"Player", L"..\\Resources\\Image\\Player\\player.bmp"));
		
		SetComponent();

		InitSkill(mDubleTab, 60.f, 50.f, 2, mOffenceStat.attackSpeed * 0.14f, mOffenceStat.attackSpeed * 0.4f);
		InitSkill(mFMJ, 230.f, 120.f, 1, 0.60f, 3.0f, eStagger::Nomal);
		InitSkill(mTacticalDive, 0.f, mUtilityStat.moveSpeed * 100.f, 1, 0.70f, 5.0f);
		InitSkill(mSupressiveFire, 800.f, 60.f, 6, mOffenceStat.attackSpeed * 0.14f, 5.0f, eStagger::Heave);
	}
	void Player::SetComponent()
	{
		Creature::SetComponent();
		InitAnim();

		mBodyCollider->SetSize(Size(PLAYER_SIZE_X, PLAYER_SIZE_Y) * GetScale());
		mBodyCollider->SetOffset(Vector2(-10.f, 0.f));

		mFootCollider->SetSize(Size(15, 5));
		mFootCollider->SetOffset(Vector2(-9, 20));
	}
	void Player::InitAnim()
	{
		mAnimator->CreateAnimation(L"PIdleR", mSpriteImage, Pos(0.f, 0.f), Size(30.f, 36.f)
			, Vector2(-10.f, 0.f), 1, 0.1f);
		mAnimator->CreateAnimation(L"PIdleL", mSpriteImage, Pos(0.f, 36.f), Size(30.f, 36.f)
			, Vector2(-8.f, 0.f), 1, 0.1f);

		mAnimator->CreateAnimation(L"PWalkR", mSpriteImage, Pos(0.f, 72.f), Size(18.0f, 33.f)
			, Vector2(-10.f, 0.f), 8, 0.1f);
		mAnimator->CreateAnimation(L"PWalkL", mSpriteImage, Pos(0.f, 105.f), Size(18.0f, 33.f)
			, Vector2(-10.f, 0.f), 8, 0.1f);

		mAnimator->CreateAnimation(L"PJumpR", mSpriteImage, Pos(0.f, 504.f), Size(18.0f, 33.f)
			, Vector2(-10.f, 0.f), 1, 0.1f);
		mAnimator->CreateAnimation(L"PJumpL", mSpriteImage, Pos(0.f, 537.f), Size(18.0f, 33.f)
			, Vector2(-10.f, 0.f), 1, 0.1f);

		mAnimator->CreateAnimation(L"PClimb", mSpriteImage, Pos(0.f, 570.f), Size(18.0f, 36.f)
			, Vector2(-10.f, 0.f), 2, 0.1f);

		mAnimator->CreateAnimation(L"PDeathR", mSpriteImage, Pos(0.f, 606.f), Size(54.0f, 27.f)
			, Vector2(-25.f, 5.f), 5, 0.1f);
		mAnimator->CreateAnimation(L"PDeathL", mSpriteImage, Pos(0.f, 633.f), Size(54.0f, 27.f)
			, Vector2(25.f, 5.f), 5, 0.1f);



		mAnimator->CreateAnimation(L"PDubleTabR", mSpriteImage, Pos(0.f, 138.f), Size(60.f, 36.f)
			, Vector2(2.f, 0.f), 5, 0.08f);
		mAnimator->CreateAnimation(L"PDubleTabL", mSpriteImage, Pos(0.f, 174.f), Size(60.f, 36.f)
			, Vector2(-25.f, 0.f), 5, 0.08f);

		mAnimator->CreateAnimation(L"PFMJR", mSpriteImage, Pos(0.f, 210.f), Size(96.0f, 33.f)
			, Vector2(23.f, 0.f), 5, 0.1f);
		mAnimator->CreateAnimation(L"PFMJL", mSpriteImage, Pos(0.f, 243.f), Size(96.0f, 33.f)
			, Vector2(-45.f, 0.f), 5, 0.1f);

		mAnimator->CreateAnimation(L"PDiveR", mSpriteImage, Pos(0.f, 276.f), Size(36.f, 36.f)
			, Vector2(-12.f, 0.f), 9, 0.1f);
		mAnimator->CreateAnimation(L"PDiveL", mSpriteImage, Pos(0.f, 312.f), Size(36.f, 36.f)
			, Vector2(-8.f, 0.f), 9, 0.1f);

		mAnimator->CreateAnimation(L"PSuppressiveFireR", mSpriteImage, Pos(0.f, 348.f), Size(114.f, 39.f)
			, Vector2(-10.f, 0.f), 15, 0.08f);
		mAnimator->CreateAnimation(L"PSuppressiveFireL", mSpriteImage, Pos(0.f, 387.f), Size(114.f, 39.f)
			, Vector2(-10.f, 0.f), 15, 0.08f);
		mAnimator->CreateAnimation(L"PSuppressiveFireBothR", mSpriteImage, Pos(0.f, 426.f), Size(114.f, 39.f)
			, Vector2(0.f, 0.f), 15, 0.08f);
		mAnimator->CreateAnimation(L"PSuppressiveFireBothL", mSpriteImage, Pos(0.f, 465.f), Size(114.f, 39.f)
			, Vector2(0.f, 0.f), 15, 0.08f);

		mAnimator->Play(L"PIdleR");
		//mAnimator->GetCompleteEvents(L"PDubleTabR") = std::bind(&Player::ReturnIdle, this);
		//mAnimator->GetCompleteEvents(L"PDubleTabL") = std::bind(&Player::ReturnIdle, this);
		//mAnimator->GetCompleteEvents(L"PDiveR") = std::bind(&Player::ReturnIdle, this);
		//mAnimator->GetCompleteEvents(L"PDiveL") = std::bind(&Player::ReturnIdle, this);
		//mAnimator->GetCompleteEvents(L"PFMJR") = std::bind(&Player::ReturnIdle, this);
		//mAnimator->GetCompleteEvents(L"PFMJL") = std::bind(&Player::ReturnIdle, this);
		//mAnimator->GetCompleteEvents(L"PSuppressiveFireR") = std::bind(&Player::ReturnIdle, this);
		//mAnimator->GetCompleteEvents(L"PSuppressiveFireL") = std::bind(&Player::ReturnIdle, this);
		//mAnimator->GetCompleteEvents(L"PSuppressiveFireBothR") = std::bind(&Player::ReturnIdle, this);
		//mAnimator->GetCompleteEvents(L"PSuppressiveFireBothL") = std::bind(&Player::ReturnIdle, this);
	}

	void Player::InitSkill(SkillInfo& skill, float damage, float power, int maxCount
		, float castDelay, float coolDown, eStagger	stagger)
	{
		skill.damage = damage;
		skill.power = power;
		skill.maxCount = maxCount;
		skill.curCount = 0;
		skill.castDelay = castDelay;
		skill.castDelayTime = 0.0f;
		skill.coolDown = coolDown;
		skill.coolDownTime = 0.0f;
		skill.active = false;
		skill.run = false;
		skill.finish = false;
		skill.stagger = stagger;
	}

	void Player::Tick()
	{
		// Death 상태일경우 ret

		// 본인 컴포넌트 Tick 호출
		mFootObject->Tick();
		GameObject::Tick();

		// 스킬 기능
		Cooldown();
		SkillProcess();
		// 상태 기능
		switch (mState)
		{
		case ePlayerState::Idle:
		{
			Idle();
		}
		break;
		case ePlayerState::Move:
		{
			Move();
		}
		break;
		case ePlayerState::Jump:
		{
			Jump();
		}
		break;
		case ePlayerState::Climb:
		{
			Climb();
		}
		break;
		case ePlayerState::DoubleTab:
		{
			DoubleTab();
		}
		break;
		case ePlayerState::FMJ:
		{
			FMJ();
		}
		break;
		case ePlayerState::SupressiveFire:
		{
			SupressiveFire();
		}
		break;
		case ePlayerState::TacticalDive:
		{
			TacticalDive();
		}
		break;
		case ePlayerState::Death:
		{
			Death();
		}
		break;
		}
	}
	void Player::Cooldown()
	{
		if (true == mDubleTab.active)
		{
			mDubleTab.coolDownTime += Time::GetDeltaTime();
			if (mDubleTab.coolDownTime > mDubleTab.coolDown)
			{
				mDubleTab.active = false;
				mDubleTab.coolDownTime = 0.0f;
			}
		}
		if (true == mFMJ.active)
		{
			mFMJ.coolDownTime += Time::GetDeltaTime();
			if (mFMJ.coolDownTime > mFMJ.coolDown)
			{
				mFMJ.active = false;
				mFMJ.coolDownTime = 0.0f;
			}
		}
		if (true == mTacticalDive.active)
		{
			mTacticalDive.coolDownTime += Time::GetDeltaTime();
			if (mTacticalDive.coolDownTime > mTacticalDive.coolDown)
			{
				mTacticalDive.active = false;
				mTacticalDive.coolDownTime = 0.0f;
			}
		}
		if (true == mSupressiveFire.active)
		{
			mSupressiveFire.coolDownTime += Time::GetDeltaTime();
			if (mSupressiveFire.coolDownTime > mSupressiveFire.coolDown)
			{
				mSupressiveFire.active = false;
				mSupressiveFire.coolDownTime = 0.0f;
			}
		}
	}
	void Player::SkillProcess()
	{
		// 시간을 재서 여러 호출간 딜레이를 넣어줌
		// 오브젝트 풀 호출
		if (true == mDubleTab.run)
		{
			// 딜레이 계산
			mDubleTab.castDelayTime += Time::GetDeltaTime();

			// 스킬 카운트가 유효하다면 반복
			if (mDubleTab.curCount < mDubleTab.maxCount)
			{
				// 시전 준비가 되면 발사
				if (mDubleTab.castDelayTime >= mDubleTab.castDelay)
				{
					Skill(eProjectileType::DoubleTab);
					mDubleTab.castDelayTime = 0.0f;
					++mDubleTab.curCount;
				}
			}
			else
			{
				mDubleTab.curCount = 0;
				mDubleTab.run = false;
				mDubleTab.finish = true;
			}
		}
		if (true == mFMJ.run)
		{
			// 딜레이 계산
			mFMJ.castDelayTime += Time::GetDeltaTime();

			// 횟수 제한
			if (mFMJ.curCount < mFMJ.maxCount)
			{
				Skill(eProjectileType::FMJ);
				++mFMJ.curCount;
			}

			// 딜레이 진행
			if (mFMJ.castDelayTime >= mFMJ.castDelay)
			{
				mFMJ.castDelayTime = 0.0f;
				mFMJ.curCount = 0;
				mFMJ.run = false;
				mFMJ.finish = true;
			}
		}
		if (true == mTacticalDive.run)
		{
			// 딜레이 계산
			mTacticalDive.castDelayTime += Time::GetDeltaTime();

			// 횟수 제한
			if (mTacticalDive.curCount < mTacticalDive.maxCount)
			{
				Skill(eProjectileType::TacticalDive);
				++mTacticalDive.curCount;
			}
			// 회피 로직 추후 추가할 예정

			// 딜레이 진행
			if (mTacticalDive.castDelayTime >= mTacticalDive.castDelay)
			{
				mTacticalDive.castDelayTime = 0.0f;
				mTacticalDive.curCount = 0;
				mTacticalDive.run = false;
				mTacticalDive.finish = true;
			}
		}
		if (true == mSupressiveFire.run)
		{
			// 딜레이 계산
			mSupressiveFire.castDelayTime += Time::GetDeltaTime();

			// 스킬 카운트가 유효하다면 반복
			if (mSupressiveFire.curCount < mSupressiveFire.maxCount)
			{
				// 시전 준비가 되면 발사
				if (mSupressiveFire.castDelayTime >= mSupressiveFire.castDelay)
				{
					Skill(eProjectileType::SuppresiveFire);
					mSupressiveFire.castDelayTime = 0.0f;
					++mSupressiveFire.curCount;
				}
			}
			else
			{
				mSupressiveFire.curCount = 0;
				mSupressiveFire.run = false;
				mSupressiveFire.finish = true;
			}
		}
	}
	void Player::Skill(eProjectileType type)
	{
		switch (type)
		{
		case eProjectileType::DoubleTab:
		{
			// 투사체 풀에서 끌어다가 사용
			for (int idx = 0; idx < PLAYER_PROJECTILE_POOL; ++idx)
			{
				// 비활성화 투사체 찾으면
				if (mWeapon[idx]->IsAble() == false)
				{
					// Active상태로 만들고
					mWeapon[idx]->Active(type, mDubleTab.damage, mDubleTab.stagger, mDubleTab.power);
					mDubleTab.active = true;
					mDubleTab.run = true;
					break;
				}
			}
		}
		break;
		case eProjectileType::FMJ:
		{
			for (int idx = 0; idx < PLAYER_PROJECTILE_POOL; ++idx)
			{
				if (mWeapon[idx]->IsAble() == false)
				{
					mWeapon[idx]->Active(type, mFMJ.damage, mFMJ.stagger, mFMJ.power);
					mFMJ.active = true;
					mFMJ.run = true;
					break;
				}
			}
		}
		break;
		case eProjectileType::TacticalDive:
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.x = GetDir().x * mTacticalDive.power * 3.0f;
			mRigidbody->SetVelocity(velocity);

			mTacticalDive.active = true;
			mTacticalDive.run = true;
		}
		break;
		case eProjectileType::SuppresiveFire:
		{
			for (int idx = 0; idx < PLAYER_PROJECTILE_POOL; ++idx)
			{
				if (mWeapon[idx]->IsAble() == false)
				{
					mWeapon[idx]->Active(type, mSupressiveFire.damage, mSupressiveFire.stagger, mSupressiveFire.power);
					mSupressiveFire.active = true;
					mSupressiveFire.run = true;
					break;
				}
			}
		}
		break;
		}
	}

	void Player::JumpProcess()
	{
		// ground off
		mRigidbody->SetGround(false);
		// count +
		++mUtilityStat.curJumpCount;

		// set velocity
		Vector2 velocity = mRigidbody->GetVelocity();
		velocity.y = -mUtilityStat.jumpPower;
		mRigidbody->SetVelocity(velocity);
	}

	// Collider, State 시각적 디버깅
	void Player::Render(HDC hdc)
	{
		mFootObject->Render(hdc);
		GameObject::Render(hdc);
		func::DebugTextRender(hdc, L"현재 State :", std::to_wstring((int)mState), 10, 130);
	}
		
	
	// 필요없음
	/*void Player::ReturnIdle()
	{
		Vector2 dir = GetDir();
		if (dir == Vector2::Right)
			mAnimator->Play(L"PIdleR");
		else
			mAnimator->Play(L"PIdleL");
	}*/


	void Player::Idle()
	{
		// 이동 애니메이션
		if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			mAnimator->Play(L"PWalkR");
		}
		if (KEY_PRESSE(eKeyCode::LEFT))
		{
			mAnimator->Play(L"PWalkL");
		}		

		// 상태 변동
		// Move 상태 
		if (KEY_PRESSE(eKeyCode::LEFT) || KEY_PRESSE(eKeyCode::RIGHT))
		{
			mState = ePlayerState::Move;
		}
		// Jump 상태 
		if (KEY_PRESSE(eKeyCode::SPACE) && mUtilityStat.curJumpCount < mUtilityStat.maxJumpCount)
		{
			if (Vector2::Right == mDir)
				mAnimator->Play(L"PJumpR");
			else
				mAnimator->Play(L"PJumpL");
			mState = ePlayerState::Jump;
			JumpProcess();
		}

		// DoubleTab 상태 
		if (KEY_PRESSE(eKeyCode::Z))
		{
			if (false == mDubleTab.active)
			{
				if (Vector2::Right == mDir)
					mAnimator->Play(L"PDubleTabR", false);
				else
					mAnimator->Play(L"PDubleTabL", false);
				mState = ePlayerState::DoubleTab;
			}
		}
		// FMJ 상태 
		if (KEY_PRESSE(eKeyCode::X))
		{
			if (false == mFMJ.active)
			{
				if (Vector2::Right == mDir)
					mAnimator->Play(L"PFMJR", false);
				else
					mAnimator->Play(L"PFMJL", false);
				mState = ePlayerState::FMJ;
			}
		}
		// SupressiveFire 상태 
		if (KEY_PRESSE(eKeyCode::V))
		{
			if (false == mSupressiveFire.active)
			{
				if (Vector2::Right == mDir)
					mAnimator->Play(L"PSuppressiveFireR", false);
				else
					mAnimator->Play(L"PSuppressiveFireL", false);
				mState = ePlayerState::SupressiveFire;
			}
		}
		// TacticalDive 상태 
		if (KEY_PRESSE(eKeyCode::C))
		{
			if (false == mTacticalDive.active)
			{
				if (Vector2::Right == mDir)
					mAnimator->Play(L"PDiveR", false);
				else
					mAnimator->Play(L"PDiveL", false);
				mState = ePlayerState::TacticalDive;
			}
		}
	}
	void Player::Move()
	{
		// 대기 애니메이션
		if (KEY_UP(eKeyCode::RIGHT))
		{
			mAnimator->Play(L"PIdleR");
		}
		if (KEY_UP(eKeyCode::LEFT))
		{
			mAnimator->Play(L"PIdleL");
		}

		// 로직
		if (KEY_PRESSE(eKeyCode::LEFT))
		{
			SetDir(Vector2::Left);
			Vector2 curVelocity = mRigidbody->GetVelocity();
			curVelocity.x = mDir.x * mUtilityStat.moveSpeed * 100;
			mRigidbody->SetVelocity(curVelocity);
		}
		if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			SetDir(Vector2::Right);
			Vector2 curVelocity = mRigidbody->GetVelocity();
			curVelocity.x = mDir.x * mUtilityStat.moveSpeed * 100;
			mRigidbody->SetVelocity(curVelocity);
		}

		// 상태 변동
		// Idle 상태 
		if (KEY_UP(eKeyCode::LEFT) || KEY_UP(eKeyCode::RIGHT))
		{
			mState = ePlayerState::Idle;
		}
		// Jump 상태
		if (KEY_PRESSE(eKeyCode::SPACE) && mUtilityStat.curJumpCount < mUtilityStat.maxJumpCount)
		{
			if (Vector2::Right == mDir)
				mAnimator->Play(L"PJumpR");
			else
				mAnimator->Play(L"PJumpL");
			mState = ePlayerState::Jump;
			JumpProcess();
		}

		// DoubleTab 상태 
		if (KEY_PRESSE(eKeyCode::Z))
		{
			if (false == mDubleTab.active)
			{
				if (Vector2::Right == mDir)
					mAnimator->Play(L"PDubleTabR", false);
				else
					mAnimator->Play(L"PDubleTabL", false);
				mState = ePlayerState::DoubleTab;
			}
		}
		// FMJ 상태 
		if (KEY_PRESSE(eKeyCode::X))
		{
			if (false == mFMJ.active)
			{
				if (Vector2::Right == mDir)
					mAnimator->Play(L"PFMJR", false);
				else
					mAnimator->Play(L"PFMJL", false);
				mState = ePlayerState::FMJ;
			}
		}
		// SupressiveFire 상태 
		if (KEY_PRESSE(eKeyCode::V))
		{
			if (false == mSupressiveFire.active)
			{
				if (Vector2::Right == mDir)
					mAnimator->Play(L"PSuppressiveFireR", false);
				else
					mAnimator->Play(L"PSuppressiveFireL", false);
				mState = ePlayerState::SupressiveFire;
			}
		}
		// TacticalDive 상태 
		if (KEY_PRESSE(eKeyCode::C))
		{
			if (false == mTacticalDive.active)
			{
				if (Vector2::Right == mDir)
					mAnimator->Play(L"PDiveR", false);
				else
					mAnimator->Play(L"PDiveL", false);
				mState = ePlayerState::TacticalDive;
			}
		}
	}
	void Player::Jump()
	{
		// 점프 애니메이션
		if (KEY_DOWN(eKeyCode::RIGHT))
		{
			mAnimator->Play(L"PJumpR");
		}
		if (KEY_DOWN(eKeyCode::LEFT))
		{
			mAnimator->Play(L"PJumpL");
		}

		// 로직
		if (KEY_DOWN(eKeyCode::SPACE) && mUtilityStat.curJumpCount < mUtilityStat.maxJumpCount)
		{
			JumpProcess();			
		}
		if (KEY_PRESSE(eKeyCode::LEFT))
		{
			SetDir(Vector2::Left);
			Vector2 curVelocity = mRigidbody->GetVelocity();
			curVelocity.x = mDir.x * mUtilityStat.moveSpeed * 100;
			mRigidbody->SetVelocity(curVelocity);
			/*SetDir(Vector2::Left);
			GetComponent<Rigidbody>()->AddForce(Vector2::Left * mUtilityStat.moveSpeed)*/;
		}
		if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			SetDir(Vector2::Right);
			Vector2 curVelocity = mRigidbody->GetVelocity();
			curVelocity.x = mDir.x * mUtilityStat.moveSpeed * 100;
			mRigidbody->SetVelocity(curVelocity);
			/*SetDir(Vector2::Right);
			GetComponent<Rigidbody>()->AddForce(Vector2::Right * mUtilityStat.moveSpeed);*/
		}

		// 상태 변동
		// Idle 상태 
		if (true == mRigidbody->IsGrounded())
		{
			if (Vector2::Right == mDir)
				mAnimator->Play(L"PIdleR");
			else
				mAnimator->Play(L"PIdleL");
			mState = ePlayerState::Idle;
		}		
		// DoubleTab 상태 
		if (KEY_PRESSE(eKeyCode::Z))
		{
			if (false == mDubleTab.active)
			{
				if (Vector2::Right == mDir)
					mAnimator->Play(L"PDubleTabR", false);
				else
					mAnimator->Play(L"PDubleTabL", false);
				mState = ePlayerState::DoubleTab;
			}
		}
		// FMJ 상태 
		if (KEY_DOWN(eKeyCode::X))
		{
			if (false == mFMJ.active)
			{
				if (Vector2::Right == mDir)
					mAnimator->Play(L"PFMJR", false);
				else
					mAnimator->Play(L"PFMJL", false);
				mState = ePlayerState::FMJ;
			}
		}
		// SupressiveFire 상태 
		if (KEY_DOWN(eKeyCode::V))
		{
			if (false == mSupressiveFire.active)
			{
				if (Vector2::Right == mDir)
					mAnimator->Play(L"PSuppressiveFireR", false);
				else
					mAnimator->Play(L"PSuppressiveFireL", false);
				mState = ePlayerState::SupressiveFire;
			}
		}
		// TacticalDive 상태 
		if (KEY_DOWN(eKeyCode::C))
		{
			if (false == mTacticalDive.active)
			{
				if (Vector2::Right == mDir)
					mAnimator->Play(L"PDiveR", false);
				else
					mAnimator->Play(L"PDiveL", false);
				mState = ePlayerState::TacticalDive;
			}
		}
	}
	void Player::DoubleTab()
	{		
		// 로직
		if (KEY_PRESSE(eKeyCode::Z))
		{
			if (false == mDubleTab.active)
				Skill(eProjectileType::DoubleTab);
		}
		
		// 상태 변동
		// Idle 상태
		if (true == mDubleTab.finish)
		{
			if (Vector2::Right == mDir)
				mAnimator->Play(L"PIdleR");
			else
				mAnimator->Play(L"PIdleL");
			mState = ePlayerState::Idle;
			mDubleTab.finish = false;
		}
	}
	void Player::FMJ()
	{
		// 로직
		if (false == mFMJ.active)
			Skill(eProjectileType::FMJ);

		// 상태 변동
		// Idle 상태 
		if (true == mFMJ.finish)
		{
			if (Vector2::Right == mDir)
				mAnimator->Play(L"PIdleR");
			else
				mAnimator->Play(L"PIdleL");
			mState = ePlayerState::Idle;
			mFMJ.finish = false;
		}
	}
	void Player::TacticalDive()
	{
		// 로직		
		if (false == mTacticalDive.active)
			Skill(eProjectileType::TacticalDive);
		
		// 상태 변동
		// Idle 상태 
		if (true == mTacticalDive.finish)
		{
			if (Vector2::Right == mDir)
				mAnimator->Play(L"PIdleR");
			else
				mAnimator->Play(L"PIdleL");
			mState = ePlayerState::Idle;
			mTacticalDive.finish = false;
		}
	}
	void Player::SupressiveFire()
	{
		if (false == mSupressiveFire.active)
			Skill(eProjectileType::SuppresiveFire);

		// 상태 변동
		// Idle 상태 
		if (true == mSupressiveFire.finish)
		{
			if (Vector2::Right == mDir)
				mAnimator->Play(L"PIdleR");
			else
				mAnimator->Play(L"PIdleL");
			mState = ePlayerState::Idle;
			mSupressiveFire.finish = false;
		}
	}

	// 나중에 구현
	void Player::Climb()
	{
		// 로직
		if (KEY_PRESSE(eKeyCode::UP))
		{
			mRigidbody->AddForce(Vector2::Up * mUtilityStat.moveSpeed);
		}
		if (KEY_PRESSE(eKeyCode::DOWN))
		{
			mRigidbody->AddForce(Vector2::Down * mUtilityStat.moveSpeed);
		}

		// 상태 변동 (조건 : 벽과 충돌여부)
		if (KEY_DOWN(eKeyCode::SPACE) && false == mBlocked)
		{
			mRigidbody->SetGround(false);
			mState = ePlayerState::Jump;
		}
		if (KEY_DOWN(eKeyCode::C) && false == mBlocked)
		{
			if (false == mTacticalDive.active)
			{
				mRigidbody->SetGround(false);

				if (Vector2::Right == mDir)
					mAnimator->Play(L"PDiveR", false);
				else
					mAnimator->Play(L"PDiveL", false);
				mState = ePlayerState::TacticalDive;
			}
		}
	}
	void Player::Death()
	{
		// ..?
		// 게임 종료 UI 불러오기
	}
	


	void Player::OnCollisionEnter(Collider* other)
	{
		eColliderLayer type = other->GetOwner()->GetType();

		// 벽에 닿음
		if (type == eColliderLayer::Platform)
		{
			mBlocked = true;
		}
		
		// 공격 받음
		if (type == eColliderLayer::DamagingObj)
		{
			Creature* attacker = dynamic_cast<Creature*>(other->GetOwner());
			Offence offence = attacker->GetOffence();
			Creature::SelfHit(other->GetOwner(), offence.damage, eStagger::Nomal);
		}
	}
	void Player::OnCollisionStay(Collider* other)
	{
	}
	void Player::OnCollisionExit(Collider* other)
	{
		eColliderLayer type = other->GetOwner()->GetType();

		if (type == eColliderLayer::Platform)
		{
			mBlocked = false;
		}
	}
}