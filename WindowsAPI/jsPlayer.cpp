#include "jsPlayer.h"
#include "jsTime.h"
#include "jsInput.h"
#include "jsProjectile.h"
#include "jsSceneManager.h"
#include "jsScene.h"
#include "jsImage.h"
#include "jsResources.h"
#include "jsCamera.h"


#include "jsAnimator.h"
#include "jsCollider.h"
#include "jsRigidbody.h"

namespace js
{
	Player::Player()
		: mSpeed(300.f)
		, mImage(nullptr)
		, mDir(Vector2::Right)
	{
		// 내 초기값 세팅
		SetPos(Pos(400.f, 1000.f));
		SetScale(Size(1.f, 1.f));

		Init();
	}
	Player::Player(Pos pos)
		: mSpeed(300.f)
		, mImage(nullptr)
		, mDir(Vector2::Right)
	{
		SetPos(pos);
		SetScale(Size(1.f, 1.f));

		Init();		
	}
	Player::~Player()
	{
	}

	void Player::Init()
	{
		// 이미지 리소스 로딩
		if (nullptr == mImage)
		{
			mImage = Resources::Load<Image>
				(L"Player", L"..\\Resources\\Image\\Player\\player.bmp");
		}
		// 애니메이터 설정
		InitAnim();
		mAnimator->Play(L"IdleR");
		// 콜라이더 설정
		mCollider = new Collider;
		mCollider->SetPos(GetPos());
		mCollider->SetScale(Size(7.f, 12.f) * GetScale());
		mCollider->SetOffset(Vector2(-10.f, 0.f));
		AddComponent(mCollider);
		// 강체 설정
		mRigidbody = AddComponent<Rigidbody>();
	}

	void Player::InitAnim()
	{
		mAnimator = new Animator;
		AddComponent(mAnimator);

		mAnimator->CreateAnimation(L"IdleR", mImage, Pos(0.f, 0.f), Size(30.f, 36.f)
			, Vector2(-10.f, 0.f), 1, 0.1f);
		mAnimator->CreateAnimation(L"IdleL", mImage, Pos(0.f, 36.f), Size(30.f, 36.f)
			, Vector2(-8.f, 0.f), 1, 0.1f);

		mAnimator->CreateAnimation(L"WalkR", mImage, Pos(0.f, 72.f), Size(18.0f, 33.f)
			, Vector2(-10.f, 0.f), 8, 0.1f);
		mAnimator->CreateAnimation(L"WalkL", mImage, Pos(0.f, 105.f), Size(18.0f, 33.f)
			, Vector2(-10.f, 0.f), 8, 0.1f);

		mAnimator->CreateAnimation(L"JumpR", mImage, Pos(0.f, 504.f), Size(18.0f, 33.f)
			, Vector2(-10.f, 0.f), 1, 0.1f);
		mAnimator->CreateAnimation(L"JumpL", mImage, Pos(0.f, 537.f), Size(18.0f, 33.f)
			, Vector2(-10.f, 0.f), 1, 0.1f);

		mAnimator->CreateAnimation(L"Climb", mImage, Pos(0.f, 570.f), Size(18.0f, 36.f)
			, Vector2(-10.f, 0.f), 2, 0.1f);

		mAnimator->CreateAnimation(L"DeathR", mImage, Pos(0.f, 606.f), Size(54.0f, 27.f)
			, Vector2(-25.f, 5.f), 5, 0.1f);
		mAnimator->CreateAnimation(L"DeathL", mImage, Pos(0.f, 633.f), Size(54.0f, 27.f)
			, Vector2(25.f, 5.f), 5, 0.1f);





		mAnimator->CreateAnimation(L"DubleTabR", mImage, Pos(0.f, 138.f), Size(60.f, 36.f)
			, Vector2(2.f, 0.f), 5, 0.08f);
		mAnimator->CreateAnimation(L"DubleTabL", mImage, Pos(0.f, 174.f), Size(60.f, 36.f)
			, Vector2(-25.f, 0.f), 5, 0.08f);

		mAnimator->CreateAnimation(L"FMJR", mImage, Pos(0.f, 210.f), Size(96.0f, 33.f)
			, Vector2(23.f, 0.f), 5, 0.1f);
		mAnimator->CreateAnimation(L"FMJL", mImage, Pos(0.f, 243.f), Size(96.0f, 33.f)
			, Vector2(-45.f, 0.f), 5, 0.1f);

		mAnimator->CreateAnimation(L"DiveR", mImage, Pos(0.f, 276.f), Size(36.f, 36.f)
			, Vector2(-12.f, 0.f), 9, 0.1f);
		mAnimator->CreateAnimation(L"DiveL", mImage, Pos(0.f, 312.f), Size(36.f, 36.f)
			, Vector2(-8.f, 0.f), 9, 0.1f);

		mAnimator->CreateAnimation(L"SuppressiveFireR", mImage, Pos(0.f, 348.f), Size(114.f, 39.f)
			, Vector2(0.f, 0.f), 15, 0.08f);
		mAnimator->CreateAnimation(L"SuppressiveFireL", mImage, Pos(0.f, 387.f), Size(114.f, 39.f)
			, Vector2(0.f, 0.f), 15, 0.08f);
		mAnimator->CreateAnimation(L"SuppressiveFireBothR", mImage, Pos(0.f, 426.f), Size(114.f, 39.f)
			, Vector2(0.f, 0.f), 15, 0.08f);
		mAnimator->CreateAnimation(L"SuppressiveFireBothL", mImage, Pos(0.f, 465.f), Size(114.f, 39.f)
			, Vector2(0.f, 0.f), 15, 0.08f);

		mAnimator->GetCompleteEvents(L"DubleTabR") = std::bind(&Player::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"DubleTabL") = std::bind(&Player::ReturnIdle, this);

		mAnimator->GetCompleteEvents(L"DiveR") = std::bind(&Player::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"DiveL") = std::bind(&Player::ReturnIdle, this);

		mAnimator->GetCompleteEvents(L"FMJR") = std::bind(&Player::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"FMJL") = std::bind(&Player::ReturnIdle, this);

		mAnimator->GetCompleteEvents(L"SuppressiveFireR") = std::bind(&Player::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"SuppressiveFireL") = std::bind(&Player::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"SuppressiveFireBothR") = std::bind(&Player::ReturnIdle, this);
		mAnimator->GetCompleteEvents(L"SuppressiveFireBothL") = std::bind(&Player::ReturnIdle, this);

	}

	void Player::Tick()
	{
		GameObject::Tick();
	
		// 애니메이션
		PlayAnim();
		
		// 로직
		if (KEY_PRESSE(eKeyCode::UP))
		{
			GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, -200.0f));
		}
		if (KEY_PRESSE(eKeyCode::DOWN))
		{
			GetComponent<Rigidbody>()->AddForce(Vector2(0.0f, 200.0f));
		}
		if (KEY_PRESSE(eKeyCode::LEFT))
		{
			mDir = Vector2::Left;
			GetComponent<Rigidbody>()->AddForce(Vector2(-200.0f, 0.0f));
		}		
		if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			mDir = Vector2::Right;
			GetComponent<Rigidbody>()->AddForce(Vector2(200.0f, 0.0f));
		}
		/*if (KEY_DOWN(eKeyCode::Z))
		{
			Projectile* missile = new Projectile;
			Scene* playScene = SceneManager::GetPlayScene();
			playScene->AddGameObject(missile, eColliderLayer::Player_Projectile);


			Pos startPos = GetScale() / 2.f;
			Pos missilePos = (pos + startPos) - (missile->GetScale() / 2.f);
			
			missile->SetPos(missilePos);
		}*/
	}
	void Player::Render(HDC hdc)
	{

		GameObject::Render(hdc);
	}


	void Player::PlayAnim()
	{
		if (KEY_DOWN(eKeyCode::RIGHT))
		{
			mAnimator->Play(L"WalkR");
		}
		if (KEY_DOWN(eKeyCode::LEFT))
		{
			mAnimator->Play(L"WalkL");
		}
		if (KEY_DOWN(eKeyCode::Z))
		{
			if (mDir == Vector2::Right)
				mAnimator->Play(L"DubleTabR");
			else
				mAnimator->Play(L"DubleTabL");
		}
		if (KEY_DOWN(eKeyCode::X))
		{
			if (mDir == Vector2::Right)
				mAnimator->Play(L"FMJR");
			else
				mAnimator->Play(L"FMJL");
		}
		if (KEY_DOWN(eKeyCode::C))
		{
			if (mDir == Vector2::Right)
				mAnimator->Play(L"DiveR");
			else
				mAnimator->Play(L"DiveL");
		}
		if (KEY_DOWN(eKeyCode::V))
		{
			if (mDir == Vector2::Right)
				mAnimator->Play(L"SuppressiveFireR");
			else
				mAnimator->Play(L"SuppressiveFireL");
		}
		if (KEY_DOWN(eKeyCode::D))
		{
			if (mDir == Vector2::Right)
				mAnimator->Play(L"DeathR", false);
			else
				mAnimator->Play(L"DeathL", false);
		}
		if (KEY_UP(eKeyCode::RIGHT))
		{
			mAnimator->Play(L"IdleR");
		}
		if (KEY_UP(eKeyCode::LEFT))
		{
			mAnimator->Play(L"IdleL");
		}
		if (KEY_DOWN(eKeyCode::UP))
		{
			mAnimator->Play(L"Climb");
		}
		if (KEY_DOWN(eKeyCode::DOWN))
		{
			mAnimator->Play(L"Climb");
		}
		if (KEY_DOWN(eKeyCode::SPACE))
		{
			if (mDir == Vector2::Right)
				mAnimator->Play(L"JumpR");
			else
				mAnimator->Play(L"JumpL");
		}

		if (KEY_UP(eKeyCode::SPACE))
		{
			if (mDir == Vector2::Right)
				mAnimator->Play(L"IdleR");
			else
				mAnimator->Play(L"IdleL");
		}

		if (KEY_UP(eKeyCode::UP))
		{
			if (mDir == Vector2::Right)
				mAnimator->Play(L"IdleR");
			else
				mAnimator->Play(L"IdleL");
		}
		if (KEY_UP(eKeyCode::DOWN))
		{
			if (mDir == Vector2::Right)
				mAnimator->Play(L"IdleR");
			else
				mAnimator->Play(L"IdleL");
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
	void Player::WalkComplete()
	{
		// 걸을때 이팩트를 추가 하던가 말던가
	}
	void Player::ReturnIdle()
	{
		if (mDir == Vector2::Right)
			mAnimator->Play(L"IdleR");
		else
			mAnimator->Play(L"IdleL");
	}
}