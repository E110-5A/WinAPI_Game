#include "jsPlayer.h"

// 매니저
#include "jsTime.h"
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsCamera.h"

// 리소스
#include "jsImage.h"
#include "jsResources.h"

#include "jsScene.h"

// 콜라이더
#include "jsAnimator.h"
#include "jsCollider.h"
#include "jsRigidbody.h"

// 오브젝트
#include "jsProjectile.h"
#include "jsPlayerProjectile.h"


namespace js
{
	Player::Player()
		: mSpeed(0.f)
		, mImage(nullptr)
		, mWeaponID(0)
	{
		// 내 초기값 세팅
		SetPos(Pos(400.f, 1000.f));
		SetScale(Size(1.f, 1.f));
		SetDir(Vector2::Right);
		Init();
	}
	Player::Player(Pos pos)
		: mSpeed(0.f)
		, mImage(nullptr)
		, mWeaponID(0)
	{
		SetPos(pos);
		SetScale(Size(1.f, 1.f));
		SetDir(Vector2::Right);
		Init();		
	}
	Player::~Player()
	{
	}

	void Player::Init()
	{
		// 스텟 설정
		SetSpeed(1.3f);
		SetHp(100);

		// 이미지 리소스 로딩
		if (nullptr == mImage)
		{
			mImage = Resources::Load<Image>
				(L"Player", L"..\\Resources\\Image\\Player\\player.bmp");
		}
		// 스텟 초기화
		InitStat();
		// 애니메이터 설정
		InitAnim();
		mAnimator->Play(L"PIdleR");
		// 콜라이더 설정
		mCollider = new Collider;
		mCollider->SetPos(GetPos());
		mCollider->SetSize(Size(25.f, 40.f) * GetScale());
		mCollider->SetOffset(Vector2(-10.f, 0.f));
		AddComponent(mCollider);
		// 강체 설정
		mRigidbody = AddComponent<Rigidbody>();

		// 스킬 설정
		InitSkill();
	}
	void Player::InitStat()
	{
		mStat.maxHp = 110;
		mStat.curHp = 110;
		mStat.regenHp = 0.6;
		mStat.def = 0;
		mStat.moveSpeed = 1.3;
		mStat.att = 12;
		mStat.attSpeed = 1;
		mStat.range = 700;
	}
	void Player::InitAnim()
	{
		mAnimator = new Animator;
		AddComponent(mAnimator);

		mAnimator->CreateAnimation(L"PIdleR", mImage, Pos(0.f, 0.f), Size(30.f, 36.f)
			, Vector2(-10.f, 0.f), 1, 0.1f);
		mAnimator->CreateAnimation(L"PIdleL", mImage, Pos(0.f, 36.f), Size(30.f, 36.f)
			, Vector2(-8.f, 0.f), 1, 0.1f);

		mAnimator->CreateAnimation(L"PWalkR", mImage, Pos(0.f, 72.f), Size(18.0f, 33.f)
			, Vector2(-10.f, 0.f), 8, 0.1f);
		mAnimator->CreateAnimation(L"PWalkL", mImage, Pos(0.f, 105.f), Size(18.0f, 33.f)
			, Vector2(-10.f, 0.f), 8, 0.1f);

		mAnimator->CreateAnimation(L"PJumpR", mImage, Pos(0.f, 504.f), Size(18.0f, 33.f)
			, Vector2(-10.f, 0.f), 1, 0.1f);
		mAnimator->CreateAnimation(L"PJumpL", mImage, Pos(0.f, 537.f), Size(18.0f, 33.f)
			, Vector2(-10.f, 0.f), 1, 0.1f);

		mAnimator->CreateAnimation(L"PClimb", mImage, Pos(0.f, 570.f), Size(18.0f, 36.f)
			, Vector2(-10.f, 0.f), 2, 0.1f);

		mAnimator->CreateAnimation(L"PDeathR", mImage, Pos(0.f, 606.f), Size(54.0f, 27.f)
			, Vector2(-25.f, 5.f), 5, 0.1f);
		mAnimator->CreateAnimation(L"PDeathL", mImage, Pos(0.f, 633.f), Size(54.0f, 27.f)
			, Vector2(25.f, 5.f), 5, 0.1f);



		mAnimator->CreateAnimation(L"PDubleTabR", mImage, Pos(0.f, 138.f), Size(60.f, 36.f)
			, Vector2(2.f, 0.f), 5, 0.08f);
		mAnimator->CreateAnimation(L"PDubleTabL", mImage, Pos(0.f, 174.f), Size(60.f, 36.f)
			, Vector2(-25.f, 0.f), 5, 0.08f);

		mAnimator->CreateAnimation(L"PFMJR", mImage, Pos(0.f, 210.f), Size(96.0f, 33.f)
			, Vector2(23.f, 0.f), 5, 0.1f);
		mAnimator->CreateAnimation(L"PFMJL", mImage, Pos(0.f, 243.f), Size(96.0f, 33.f)
			, Vector2(-45.f, 0.f), 5, 0.1f);

		mAnimator->CreateAnimation(L"PDiveR", mImage, Pos(0.f, 276.f), Size(36.f, 36.f)
			, Vector2(-12.f, 0.f), 9, 0.1f);
		mAnimator->CreateAnimation(L"PDiveL", mImage, Pos(0.f, 312.f), Size(36.f, 36.f)
			, Vector2(-8.f, 0.f), 9, 0.1f);

		mAnimator->CreateAnimation(L"PSuppressiveFireR", mImage, Pos(0.f, 348.f), Size(114.f, 39.f)
			, Vector2(-10.f, 0.f), 15, 0.08f);
		mAnimator->CreateAnimation(L"PSuppressiveFireL", mImage, Pos(0.f, 387.f), Size(114.f, 39.f)
			, Vector2(-10.f, 0.f), 15, 0.08f);
		mAnimator->CreateAnimation(L"PSuppressiveFireBothR", mImage, Pos(0.f, 426.f), Size(114.f, 39.f)
			, Vector2(0.f, 0.f), 15, 0.08f);
		mAnimator->CreateAnimation(L"PSuppressiveFireBothL", mImage, Pos(0.f, 465.f), Size(114.f, 39.f)
			, Vector2(0.f, 0.f), 15, 0.08f);

		mAnimator->GetCompleteEvents(L"PDubleTabR") = std::bind(&Player::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"PDubleTabL") = std::bind(&Player::ReturnIdle, this);

		mAnimator->GetCompleteEvents(L"PDiveR") = std::bind(&Player::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"PDiveL") = std::bind(&Player::ReturnIdle, this);

		mAnimator->GetCompleteEvents(L"PFMJR") = std::bind(&Player::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"PFMJL") = std::bind(&Player::ReturnIdle, this);

		mAnimator->GetCompleteEvents(L"PSuppressiveFireR") = std::bind(&Player::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"PSuppressiveFireL") = std::bind(&Player::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"PSuppressiveFireBothR") = std::bind(&Player::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"PSuppressiveFireBothL") = std::bind(&Player::ReturnIdle, this);

	}
	void Player::InitSkill()
	{
		mDubleTab.damage = 60.f;
		mDubleTab.maxHit = 2;
		mDubleTab.curHit = 2;
		mDubleTab.castDelay = mStat.attSpeed * 0.14f;
		mDubleTab.castDelayTime = 0.0f;
		mDubleTab.coolDown = mStat.attSpeed * 0.4f;
		mDubleTab.coolDownTime = 0.0f;
		mDubleTab.unable = false;
		mDubleTab.on = false;

		mFMJ.damage = 230.f;
		mFMJ.maxHit = 1;
		mFMJ.curHit = 1;
		mFMJ.castDelay = mStat.attSpeed * 0.8;
		mFMJ.castDelayTime = 0.0f;
		mFMJ.coolDown = 3.0f;
		mFMJ.coolDownTime = 0.0f;
		mFMJ.unable = false;
		mFMJ.on = false;

		mTacticalDive.damage = 0.f;
		mTacticalDive.maxHit = 0;
		mTacticalDive.curHit = 0;
		mTacticalDive.castDelay = 1.f;
		mTacticalDive.castDelayTime = 0.0f;
		mTacticalDive.coolDown = 5.0f;
		mTacticalDive.coolDownTime = 0.0f;
		mTacticalDive.unable = false;
		mTacticalDive.on = false;

		mSupressiveFire.damage = 60.f;
		mSupressiveFire.maxHit = 6;
		mSupressiveFire.curHit = 0;
		mSupressiveFire.castDelay = mStat.attSpeed * 0.14f;
		mSupressiveFire.castDelayTime = 0.0f;
		mSupressiveFire.coolDown = 5.0f;
		mSupressiveFire.coolDownTime = 0.0f;
		mSupressiveFire.unable = false;
		mSupressiveFire.on = false;
	}

	void Player::Tick()
	{
		GameObject::Tick();

		// 애니메이션
		PlayAnim();
		
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
		case ePlayerState::Attack:
		{
			Attack();
		}
		break;
		case ePlayerState::Dodge:
		{
			Dodge();
		}
		break;
		case ePlayerState::Die:
		{
			Die();
		}
		break;
		}


		Cooldown();
		SkillProcess();

		if (KEY_DOWN(eKeyCode::Z))
		{
			// 비활성 상태면 return
			if (true == mDubleTab.unable)
				return;
			else
			{
				Attack(ePlayerAttackType::DubleTab);
				mDubleTab.unable = true;
				mDubleTab.on = true;
			}
		}
		if (KEY_DOWN(eKeyCode::X))
		{
			if (true == mFMJ.unable)
				return;
			else
			{
				Attack(ePlayerAttackType::FMJ);
				mFMJ.unable = true;
				mFMJ.on = true;
			}
		}
		if (KEY_DOWN(eKeyCode::C))
		{
			if (mTacticalDive.unable)
				return;
			else
			{
				Vector2 velocity = mRigidbody->GetVelocity();

				velocity.x = GetDir().x * 300.0f * mSpeed;
				mRigidbody->SetVelocity(velocity);
				mTacticalDive.unable = true;
			}
		}
		if (KEY_DOWN(eKeyCode::V))
		{
			if (mSupressiveFire.unable)
				return;
			else
			{
				Attack(ePlayerAttackType::SuppresiveFire);
				mSupressiveFire.unable = true;
				mSupressiveFire.on = true;
			}
		}

		if (KEY_PRESSE(eKeyCode::UP))
		{
			GetComponent<Rigidbody>()->AddForce(Vector2::Up * mSpeed);
		}
		if (KEY_PRESSE(eKeyCode::DOWN))
		{
			GetComponent<Rigidbody>()->AddForce(Vector2::Down * mSpeed);
		}
		if (KEY_PRESSE(eKeyCode::LEFT))
		{
			SetDir(Vector2::Left);
			GetComponent<Rigidbody>()->AddForce(Vector2::Left * mSpeed);
		}		
		if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			SetDir(Vector2::Right);
			GetComponent<Rigidbody>()->AddForce(Vector2::Right * mSpeed);
		}

		if (KEY_DOWN(eKeyCode::SPACE))
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y = -500.0f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
		}


	}

	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);
	}
	void Player::PlayAnim()
	{
		if (KEY_DOWN(eKeyCode::RIGHT))
		{
			mAnimator->Play(L"PWalkR");
		}
		if (KEY_DOWN(eKeyCode::LEFT))
		{
			mAnimator->Play(L"PWalkL");
		}
		if (KEY_DOWN(eKeyCode::Z))
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"PDubleTabR");
			else
				mAnimator->Play(L"PDubleTabL");
		}
		if (KEY_DOWN(eKeyCode::X))
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"PFMJR");
			else
				mAnimator->Play(L"PFMJL");
		}
		if (KEY_DOWN(eKeyCode::C))
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"PDiveR");
			else
				mAnimator->Play(L"PDiveL");
		}
		if (KEY_DOWN(eKeyCode::V))
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"PSuppressiveFireR");
			else
				mAnimator->Play(L"PSuppressiveFireL");
		}
		if (KEY_DOWN(eKeyCode::D))
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"PDeathR", false);
			else
				mAnimator->Play(L"PDeathL", false);
		}
		if (KEY_UP(eKeyCode::RIGHT))
		{
			mAnimator->Play(L"PIdleR");
		}
		if (KEY_UP(eKeyCode::LEFT))
		{
			mAnimator->Play(L"PIdleL");
		}
		if (KEY_DOWN(eKeyCode::UP))
		{
			mAnimator->Play(L"PClimb");
		}
		if (KEY_DOWN(eKeyCode::DOWN))
		{
			mAnimator->Play(L"PClimb");
		}
		if (KEY_DOWN(eKeyCode::SPACE))
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"PJumpR");
			else
				mAnimator->Play(L"PJumpL");
		}

		if (KEY_UP(eKeyCode::SPACE))
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"PIdleR");
			else
				mAnimator->Play(L"PIdleL");
		}

		if (KEY_UP(eKeyCode::UP))
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"PIdleR");
			else
				mAnimator->Play(L"PIdleL");
		}
		if (KEY_UP(eKeyCode::DOWN))
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"PIdleR");
			else
				mAnimator->Play(L"PIdleL");
		}

	}

	// Done
	void Player::Cooldown()
	{
		if (true == mDubleTab.unable)
		{
			mDubleTab.coolDownTime += Time::GetDeltaTime();
			if (mDubleTab.coolDownTime > mDubleTab.coolDown)
			{
				mDubleTab.unable = false;
				mDubleTab.coolDownTime = 0.0f;
			}
		}
		if (true == mFMJ.unable)
		{
			mFMJ.coolDownTime += Time::GetDeltaTime();
			if (mFMJ.coolDownTime > mFMJ.coolDown)
			{
				mFMJ.unable = false;
				mFMJ.coolDownTime = 0.0f;
			}
		}
		if (true == mTacticalDive.unable)
		{
			mTacticalDive.coolDownTime += Time::GetDeltaTime();
			if (mTacticalDive.coolDownTime > mTacticalDive.coolDown)
			{
				mTacticalDive.unable = false;
				mTacticalDive.coolDownTime = 0.0f;
			}
		}
		if (true == mSupressiveFire.unable)
		{
			mSupressiveFire.coolDownTime += Time::GetDeltaTime();
			if (mSupressiveFire.coolDownTime > mSupressiveFire.coolDown)
			{
				mSupressiveFire.unable = false;
				mSupressiveFire.coolDownTime = 0.0f;
			}
		}
	}

	// 테스트 진행중
	void Player::SkillProcess()
	{
		// 시간을 재서 여러 호출간 딜레이를 넣어줌
		// 오브젝트 풀 호출
		// 해당 스킬이 on 일 경우에만 작동함
		
		// 스킬 시전 on
		if (true == mDubleTab.on)
		{
			// 딜레이 계산
			mDubleTab.castDelayTime += Time::GetDeltaTime();

			// while문 잘못씀
			// 스킬 카운트가 유효하다면 반복
			if (mDubleTab.curHit < mDubleTab.maxHit)
			{
				// 시전 준비가 되면 발사
				if (mDubleTab.castDelayTime >= mDubleTab.castDelay)
				{
					Attack(ePlayerAttackType::DubleTab);
					mDubleTab.castDelayTime = 0.0f;
					++mDubleTab.curHit;
				}
			}
			else
			{
				mDubleTab.curHit = 0;
				mDubleTab.on = false;
			}
		}
		if (true == mSupressiveFire.on)
		{
			// 딜레이 계산
			mSupressiveFire.castDelayTime += Time::GetDeltaTime();

			// while문 잘못씀
			// 스킬 카운트가 유효하다면 반복
			if (mSupressiveFire.curHit < mSupressiveFire.maxHit)
			{
				// 시전 준비가 되면 발사
				if (mSupressiveFire.castDelayTime >= mSupressiveFire.castDelay)
				{
					Attack(ePlayerAttackType::SuppresiveFire);
					mSupressiveFire.castDelayTime = 0.0f;
					++mSupressiveFire.curHit;
				}
			}
			else
			{
				mSupressiveFire.curHit = 0;
				mSupressiveFire.on = false;
			}
		}
	}

	// 추후 수정해야함
	void Player::Attack(ePlayerAttackType type)
	{
		switch (type)
		{
		case ePlayerAttackType::DubleTab:
		{
			// 투사체 풀에서 끌어다가 사용
			for (int idx = 0; idx < WEAPON_POOL; ++idx)
			{
				if (mWeapon[idx]->IsActive() == false)
				{
					mWeapon[idx]->Active(type, mDubleTab.damage);
					break;
				}
			}
		}
		break;
		case ePlayerAttackType::FMJ:
		{
			for (int idx = 0; idx < WEAPON_POOL; ++idx)
			{
				if (mWeapon[idx]->IsActive() == false)
				{
					mWeapon[idx]->Active(type, mFMJ.damage);
					break;
				}
			}
		}
		break;
		case ePlayerAttackType::SuppresiveFire:
		{
			for (int idx = 0; idx < WEAPON_POOL; ++idx)
			{
				if (mWeapon[idx]->IsActive() == false)
				{
					mWeapon[idx]->Active(type, mSupressiveFire.damage);
					break;
				}
			}
		}
		break;
		}
	}

	void Player::OnCollisionEnter(Collider* other)
	{
	}
	void Player::OnCollisionStay(Collider* other)
	{
	}
	void Player::OnCollisionExit(Collider* other)
	{
	}
	
	void Player::ReturnIdle()
	{
		Vector2 dir = GetDir();
		if (dir == Vector2::Right)
			mAnimator->Play(L"PIdleR");
		else
			mAnimator->Play(L"PIdleL");
	}
	void Player::Idle()
	{
		// 상태 변환 로직
	}
	void Player::Move()
	{
		// 상태 변환 로직
	}
	void Player::Jump()
	{
		// 만약 IsGround = true라면
		// Idle 상태로 변환
	}
	void Player::Climb()
	{
		// 사다리와 충돌중이 아니라면 Idle 상태로 변환 <- 이거 애매함 안하는게 나을듯
		// 점프 키를 누른 경우 Jump 상태로 변환
	}
	void Player::Attack()
	{
		// 상태 변환 로직
	}
	void Player::Dodge()
	{
		// 회피가 끝나면 Idle 상태로 변환
	}
	void Player::Die()
	{
		// ..?
		// 게임 종료 UI 불러오기
	}
}
/*
몬스터 Anim

Idle R,L
lt	size	length
0.0	17.21	1
0.21	=	=

Move R,L
lt	size	length
0.42	18.25	6
0.67	=	=

Teleport R,L
lt	size	length
0.92	17.21	3
0.113	=	=

Attack R,L
lt	size	length
0.134	33.21	11
0.155	=	=

Death R,L
lt	size	length
0.176	26.21	8
0.197	=	=
*/