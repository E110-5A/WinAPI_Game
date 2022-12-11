#include "jsPlayer.h"

// �Ŵ���
#include "jsTime.h"
#include "jsInput.h"
#include "jsSceneManager.h"
#include "jsCamera.h"
#include "jsPlayerManager.h"

// ���ҽ�
#include "jsImage.h"
#include "jsResources.h"

#include "jsScene.h"

// �ݶ��̴�
#include "jsAnimator.h"
#include "jsCollider.h"
#include "jsRigidbody.h"

// ������Ʈ
#include "jsPlayerProjectile.h"
#include "jsMonster.h"


namespace js
{
	Player::Player()
		: mImage(nullptr)
		, mWeaponID(0)
	{
		// �� �ʱⰪ ����
		SetPos(Pos(400.f, 1000.f));
		SetScale(Size(1.f, 1.f));
		SetDir(Vector2::Right);
		Initialize();
	}
	Player::Player(Pos pos)
		: mImage(nullptr)
		, mWeaponID(0)
	{
		SetPos(pos);
		SetScale(Size(1.f, 1.f));
		SetDir(Vector2::Right);
		Initialize();		
	}
	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		SetType(eColliderLayer::Player);
		SetName(L"Player");
		mStat = PlayerManager::GetInstance().GetPlayerStat();

		// �ִϸ��̼� ��������Ʈ �ε�
		if (nullptr == mImage)
		{
			mImage = Resources::Load<Image>
				(L"Player", L"..\\Resources\\Image\\Player\\player.bmp");
		}
		SetComponent();
		InitSkill();
	}
	void Player::SetComponent()
	{
		InitAnim();
		mAnimator->Play(L"PIdleR");

		// �ݶ��̴� ����
		mCollider = new Collider;
		AddComponent(mCollider);
		mCollider->SetPos(GetPos());
		mCollider->SetSize(Size(25.f, 40.f) * GetScale());
		mCollider->SetOffset(Vector2(-10.f, 0.f));

		// ��ü ����
		mRigidbody = AddComponent<Rigidbody>();
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

	void Player::InitSkill()
	{
		mDubleTab.damage = 60.f;
		mDubleTab.maxCount = 2;
		mDubleTab.curCount = 0;
		mDubleTab.castDelay = mStat.attSpeed * 0.14f;
		mDubleTab.castDelayTime = 0.0f;
		mDubleTab.coolDown = mStat.attSpeed * 0.4f;
		mDubleTab.coolDownTime = 0.0f;
		mDubleTab.unable = false;
		mDubleTab.on = false;
		mDubleTab.finish = false;

		mFMJ.damage = 230.f;
		mFMJ.maxCount = 1;
		mFMJ.curCount = 0;
		mFMJ.castDelay = 0.60f;
		mFMJ.castDelayTime = 0.0f;
		mFMJ.coolDown = 3.0f;
		mFMJ.coolDownTime = 0.0f;
		mFMJ.unable = false;
		mFMJ.on = false;
		mFMJ.finish = false;

		mTacticalDive.damage = 0.f;
		mTacticalDive.maxCount = 1;
		mTacticalDive.curCount = 0;
		mTacticalDive.castDelay = 0.70f;
		mTacticalDive.castDelayTime = 0.0f;
		mTacticalDive.coolDown = 5.0f;
		mTacticalDive.coolDownTime = 0.0f;
		mTacticalDive.unable = false;
		mTacticalDive.on = false;
		mTacticalDive.finish = false;

		mSupressiveFire.damage = 80.f;
		mSupressiveFire.maxCount = 6;
		mSupressiveFire.curCount = 0;
		mSupressiveFire.castDelay = mStat.attSpeed * 0.14f;
		mSupressiveFire.castDelayTime = 0.0f;
		mSupressiveFire.coolDown = 5.0f;
		mSupressiveFire.coolDownTime = 0.0f;
		mSupressiveFire.unable = false;
		mSupressiveFire.on = false;
		mSupressiveFire.finish = false;
	}

	void Player::Tick()
	{
		// Death �����ϰ�� ret

		GameObject::Tick();		
		Cooldown();
		SkillProcess();
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
	void Player::SkillProcess()
	{
		// �ð��� �缭 ���� ȣ�Ⱓ �����̸� �־���
		// ������Ʈ Ǯ ȣ��
		if (true == mDubleTab.on)
		{
			// ������ ���
			mDubleTab.castDelayTime += Time::GetDeltaTime();

			// ��ų ī��Ʈ�� ��ȿ�ϴٸ� �ݺ�
			if (mDubleTab.curCount < mDubleTab.maxCount)
			{
				// ���� �غ� �Ǹ� �߻�
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
				mDubleTab.on = false;
				mDubleTab.finish = true;
			}
		}
		if (true == mFMJ.on)
		{
			// ������ ���
			mFMJ.castDelayTime += Time::GetDeltaTime();

			// Ƚ�� ����
			if (mFMJ.curCount < mFMJ.maxCount)
			{
				Skill(eProjectileType::FMJ);
				++mFMJ.curCount;
			}

			// ������ ����
			if (mFMJ.castDelayTime >= mFMJ.castDelay)
			{
				mFMJ.castDelayTime = 0.0f;
				mFMJ.curCount = 0;
				mFMJ.on = false;
				mFMJ.finish = true;
			}
		}
		if (true == mTacticalDive.on)
		{
			// ������ ���
			mTacticalDive.castDelayTime += Time::GetDeltaTime();

			// Ƚ�� ����
			if (mTacticalDive.curCount < mTacticalDive.maxCount)
			{
				Vector2 velocity = mRigidbody->GetVelocity();
				velocity.x = GetDir().x * 300.0f * mStat.moveSpeed;
				mRigidbody->SetVelocity(velocity);
				++mTacticalDive.curCount;
			}
			// ȸ�� ���� ���� �߰��� ����


			// ������ ����
			if (mTacticalDive.castDelayTime >= mTacticalDive.castDelay)
			{
				mTacticalDive.castDelayTime = 0.0f;
				mTacticalDive.curCount = 0;
				mTacticalDive.on = false;
				mTacticalDive.finish = true;
			}
		}
		if (true == mSupressiveFire.on)
		{
			// ������ ���
			mSupressiveFire.castDelayTime += Time::GetDeltaTime();

			// ��ų ī��Ʈ�� ��ȿ�ϴٸ� �ݺ�
			if (mSupressiveFire.curCount < mSupressiveFire.maxCount)
			{
				// ���� �غ� �Ǹ� �߻�
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
				mSupressiveFire.on = false;
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
			// ����ü Ǯ���� ����ٰ� ���
			for (int idx = 0; idx < WEAPON_POOL; ++idx)
			{
				// ��� ������� ����ü ã����
				if (mWeapon[idx]->IsActive() == false)
				{
					// Active���·� �����
					mWeapon[idx]->Active(type, mDubleTab.damage);
					mDubleTab.unable = true;
					mDubleTab.on = true;
					break;
				}
			}
		}
		break;
		case eProjectileType::FMJ:
		{
			for (int idx = 0; idx < WEAPON_POOL; ++idx)
			{
				if (mWeapon[idx]->IsActive() == false)
				{
					mWeapon[idx]->Active(type, mFMJ.damage);
					mFMJ.unable = true;
					mFMJ.on = true;
					break;
				}
			}
		}
		break;
		case eProjectileType::TacticalDive:
		{
			mTacticalDive.unable = true;
			mTacticalDive.on = true;
		}
		break;
		case eProjectileType::SuppresiveFire:
		{
			for (int idx = 0; idx < WEAPON_POOL; ++idx)
			{
				if (mWeapon[idx]->IsActive() == false)
				{
					mWeapon[idx]->Active(type, mSupressiveFire.damage);
					mSupressiveFire.unable = true;
					mSupressiveFire.on = true;
					break;
				}
			}
		}
		break;
		}
	}

	// Collider, State �ð��� �����
	void Player::Render(HDC hdc)
	{
		GameObject::Render(hdc);

		wchar_t szFloat[40] = {};

		std::wstring stateStr = L"���� State :";
		stateStr += std::to_wstring((int)mState);

		swprintf_s(szFloat, 40, stateStr.c_str());
		int strLen = wcsnlen_s(szFloat, 40);
		TextOut(hdc, 10, 130, szFloat, strLen);
	}
		
	
	// �ʿ����
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
		// �̵� �ִϸ��̼�
		if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			mAnimator->Play(L"PWalkR");
		}
		if (KEY_PRESSE(eKeyCode::LEFT))
		{
			mAnimator->Play(L"PWalkL");
		}		

		// Move ���� (�ִϸ��̼� X)
		if (KEY_PRESSE(eKeyCode::LEFT) || KEY_PRESSE(eKeyCode::RIGHT))
		{
			mState = ePlayerState::Move;
		}
		// Jump ���� (�ִϸ��̼� O)
		if (KEY_DOWN(eKeyCode::SPACE))
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"PJumpR");
			else
				mAnimator->Play(L"PJumpL");
			mState = ePlayerState::Jump;
		}

		// DoubleTab ���� (�ִ� O)
		if (KEY_PRESSE(eKeyCode::Z))
		{
			if (false == mDubleTab.unable)
			{
				Vector2 dir = GetDir();
				if (dir == Vector2::Right)
					mAnimator->Play(L"PDubleTabR", false);
				else
					mAnimator->Play(L"PDubleTabL", false);
				mState = ePlayerState::DoubleTab;
			}
		}
		// FMJ ���� (�ִ� O)
		if (KEY_DOWN(eKeyCode::X))
		{
			if (false == mFMJ.unable)
			{
				Vector2 dir = GetDir();
				if (dir == Vector2::Right)
					mAnimator->Play(L"PFMJR", false);
				else
					mAnimator->Play(L"PFMJL", false);
				mState = ePlayerState::FMJ;
			}
		}
		// SupressiveFire ���� (�ִ� O)
		if (KEY_DOWN(eKeyCode::V))
		{
			if (false == mSupressiveFire.unable)
			{
				Vector2 dir = GetDir();
				if (dir == Vector2::Right)
					mAnimator->Play(L"PSuppressiveFireR", false);
				else
					mAnimator->Play(L"PSuppressiveFireL", false);
				mState = ePlayerState::SupressiveFire;
			}
		}
		// TacticalDive ���� (�ִ� O)
		if (KEY_DOWN(eKeyCode::C))
		{
			if (false == mTacticalDive.unable)
			{
				Vector2 dir = GetDir();
				if (dir == Vector2::Right)
					mAnimator->Play(L"PDiveR", false);
				else
					mAnimator->Play(L"PDiveL", false);
				mState = ePlayerState::TacticalDive;
			}
		}
	}
	void Player::Move()
	{
		// ��� �ִϸ��̼�
		if (KEY_UP(eKeyCode::RIGHT))
		{
			mAnimator->Play(L"PIdleR");
		}
		if (KEY_UP(eKeyCode::LEFT))
		{
			mAnimator->Play(L"PIdleL");
		}

		// ����
		if (KEY_PRESSE(eKeyCode::LEFT))
		{
			SetDir(Vector2::Left);
			GetComponent<Rigidbody>()->AddForce(Vector2::Left * mStat.moveSpeed);
		}
		if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			SetDir(Vector2::Right);
			GetComponent<Rigidbody>()->AddForce(Vector2::Right * mStat.moveSpeed);
		}

		// Idle ���� (�ִϸ��̼� X)
		if (KEY_UP(eKeyCode::LEFT) || KEY_UP(eKeyCode::RIGHT))
		{
			mState = ePlayerState::Idle;
		}
		// Jump ���� (�ִϸ��̼� O)
		if (KEY_DOWN(eKeyCode::SPACE))
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"PJumpR");
			else
				mAnimator->Play(L"PJumpL");
			mState = ePlayerState::Jump;
		}

		// DoubleTab ���� (�ִ� O)
		if (KEY_PRESSE(eKeyCode::Z))
		{
			if (false == mDubleTab.unable)
			{
				Vector2 dir = GetDir();
				if (dir == Vector2::Right)
					mAnimator->Play(L"PDubleTabR", false);
				else
					mAnimator->Play(L"PDubleTabL", false);
				mState = ePlayerState::DoubleTab;
			}
		}
		// FMJ ���� (�ִ� O)
		if (KEY_DOWN(eKeyCode::X))
		{
			if (false == mFMJ.unable)
			{
				Vector2 dir = GetDir();
				if (dir == Vector2::Right)
					mAnimator->Play(L"PFMJR", false);
				else
					mAnimator->Play(L"PFMJL", false);
				mState = ePlayerState::FMJ;
			}
		}
		// SupressiveFire ���� (�ִ� O)
		if (KEY_DOWN(eKeyCode::V))
		{
			if (false == mSupressiveFire.unable)
			{
				Vector2 dir = GetDir();
				if (dir == Vector2::Right)
					mAnimator->Play(L"PSuppressiveFireR", false);
				else
					mAnimator->Play(L"PSuppressiveFireL", false);
				mState = ePlayerState::SupressiveFire;
			}
		}
		// TacticalDive ���� (�ִ� O)
		if (KEY_DOWN(eKeyCode::C))
		{
			if (false == mTacticalDive.unable)
			{
				Vector2 dir = GetDir();
				if (dir == Vector2::Right)
					mAnimator->Play(L"PDiveR", false);
				else
					mAnimator->Play(L"PDiveL", false);
				mState = ePlayerState::TacticalDive;
			}
		}
	}
	void Player::Jump()
	{
		// ���� �ִϸ��̼�
		if (KEY_DOWN(eKeyCode::RIGHT))
		{
			mAnimator->Play(L"PJumpR");
		}
		if (KEY_DOWN(eKeyCode::LEFT))
		{
			mAnimator->Play(L"PJumpL");
		}

		// ����
		if (KEY_PRESSE(eKeyCode::SPACE) && true == mRigidbody->IsGrounded())
		{
			Vector2 velocity = mRigidbody->GetVelocity();
			velocity.y = -500.0f;
			mRigidbody->SetVelocity(velocity);
			mRigidbody->SetGround(false);
		}
		if (KEY_PRESSE(eKeyCode::LEFT))
		{
			SetDir(Vector2::Left);
			GetComponent<Rigidbody>()->AddForce(Vector2::Left * mStat.moveSpeed);
		}
		if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			SetDir(Vector2::Right);
			GetComponent<Rigidbody>()->AddForce(Vector2::Right * mStat.moveSpeed);
		}


		// Idle ���� (�ִϸ��̼� O)
		if (true == mRigidbody->IsGrounded())
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"PIdleR");
			else
				mAnimator->Play(L"PIdleL");
			mState = ePlayerState::Idle;
		}
		
		// DoubleTab ���� (�ִ� O)
		if (KEY_PRESSE(eKeyCode::Z))
		{
			if (false == mDubleTab.unable)
			{
				Vector2 dir = GetDir();
				if (dir == Vector2::Right)
					mAnimator->Play(L"PDubleTabR", false);
				else
					mAnimator->Play(L"PDubleTabL", false);
				mState = ePlayerState::DoubleTab;
			}
		}
		// FMJ ���� (�ִ� O)
		if (KEY_DOWN(eKeyCode::X))
		{
			if (false == mFMJ.unable)
			{
				Vector2 dir = GetDir();
				if (dir == Vector2::Right)
					mAnimator->Play(L"PFMJR", false);
				else
					mAnimator->Play(L"PFMJL", false);
				mState = ePlayerState::FMJ;
			}
		}
		// SupressiveFire ���� (�ִ� O)
		if (KEY_DOWN(eKeyCode::V))
		{
			if (false == mSupressiveFire.unable)
			{
				Vector2 dir = GetDir();
				if (dir == Vector2::Right)
					mAnimator->Play(L"PSuppressiveFireR", false);
				else
					mAnimator->Play(L"PSuppressiveFireL", false);
				mState = ePlayerState::SupressiveFire;
			}
		}
		// TacticalDive ���� (�ִ� O)
		if (KEY_DOWN(eKeyCode::C))
		{
			if (false == mTacticalDive.unable)
			{
				Vector2 dir = GetDir();
				if (dir == Vector2::Right)
					mAnimator->Play(L"PDiveR", false);
				else
					mAnimator->Play(L"PDiveL", false);
				mState = ePlayerState::TacticalDive;
			}
		}
	}
	void Player::DoubleTab()
	{		
		// ����
		if (KEY_PRESSE(eKeyCode::Z))
		{
			if (false == mDubleTab.unable)
			{
				Skill(eProjectileType::DoubleTab);
			}
		}
		
		// Idle ���� (�ִϸ��̼� O)
		if (true == mDubleTab.finish)
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"PIdleR");
			else
				mAnimator->Play(L"PIdleL");
			mState = ePlayerState::Idle;
			mDubleTab.finish = false;
		}
	}
	void Player::FMJ()
	{
		// ����
		if (false == mFMJ.unable)
		{
			Skill(eProjectileType::FMJ);
		}

		// Idle ���� (�ִϸ��̼� O)
		if (true == mFMJ.finish)
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"PIdleR");
			else
				mAnimator->Play(L"PIdleL");
			mState = ePlayerState::Idle;
			mFMJ.finish = false;
		}
	}
	void Player::TacticalDive()
	{
		// ����		
		if (false == mTacticalDive.unable)
		{
			Skill(eProjectileType::TacticalDive);
		}
		
		// Idle ���� (�ִϸ��̼� O)
		if (true == mTacticalDive.finish)
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"PIdleR");
			else
				mAnimator->Play(L"PIdleL");
			mState = ePlayerState::Idle;
			mTacticalDive.finish = false;
		}
	}
	void Player::SupressiveFire()
	{
		if (false == mSupressiveFire.unable)
		{
			Skill(eProjectileType::SuppresiveFire);
		}

		// Idle ���� (�ִϸ��̼� O)
		if (true == mSupressiveFire.finish)
		{
			Vector2 dir = GetDir();
			if (dir == Vector2::Right)
				mAnimator->Play(L"PIdleR");
			else
				mAnimator->Play(L"PIdleL");
			mState = ePlayerState::Idle;
			mSupressiveFire.finish = false;
		}
	}

	// ���߿� ����
	void Player::Climb()
	{
		// ����
		
		// ���� ��ȯ
		if (KEY_DOWN(eKeyCode::SPACE))
		{
			mState = ePlayerState::Jump;
		}
		if (KEY_DOWN(eKeyCode::C))
		{
			mState = ePlayerState::TacticalDive;
		}
	}
	void Player::Death()
	{
		// ..?
		// ���� ���� UI �ҷ�����
	}
	


	void Player::OnCollisionEnter(Collider* other)
	{
		eColliderLayer type = other->GetOwner()->GetType();

		// ���� Monster_Projectile ������� ������ ��
		if (type == eColliderLayer::Monster)
		{
			Monster* attacker = dynamic_cast<Monster*>(other->GetOwner());
			SelfDamaged(attacker);
		}
	}
	void Player::OnCollisionStay(Collider* other)
	{
	}
	void Player::OnCollisionExit(Collider* other)
	{
	}


	void Player::SelfDamaged(Monster* other) 
	{
		// �ڷ� �˹�
		Vector2 velocity = mRigidbody->GetVelocity();
		velocity.x = -GetDir().x * 150.0f;
		mRigidbody->SetVelocity(velocity);
		// ��� ����
		// ä�� ����
	}
}