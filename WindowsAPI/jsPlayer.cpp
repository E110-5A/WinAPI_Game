#include "jsPlayer.h"
#include "jsTime.h"
#include "jsInput.h"
#include "jsProjectile.h"
#include "jsSceneManager.h"
#include "jsScene.h"
#include "jsImage.h"
#include "jsResources.h"
#include "jsAnimator.h"
#include "jsCollider.h"
#include "jsCamera.h"

namespace js
{
	Player::Player()
		: mSpeed(300.f)
		, mImage(nullptr)
	{
		// 내 초기값 세팅
		SetPos(Pos(100.f, 300.f));
		SetScale(Size(3.f, 3.f));

		Init();
	}
	Player::Player(Pos pos)
		: mSpeed(300.f)
		, mImage(nullptr)
	{
		SetPos(pos);
		SetScale(Size(3.f, 3.f));

		Init();		
	}
	Player::~Player()
	{
	}

	void Player::Init()
	{
		if (nullptr == mImage)
		{
			mImage = Resources::Load<Image>
				(L"Player", L"..\\Resources\\Image\\Player\\player.bmp");
		}

		// 콜라이더 설정
		mCollider = new Collider;
		mCollider->SetPos(GetPos());
		mCollider->SetScale(Size(7.f, 12.f) * GetScale());
		mCollider->SetOffset(Vector2(-10.f, 0.f));
		AddComponent(mCollider);

		// 애니메이터 설정
		InitAnim();

		mAnimator->Play(L"IdleR");
	}

	void Player::InitAnim()
	{
		mAnimator = new Animator;
		AddComponent(mAnimator);

		mAnimator->CreateAnimation(L"IdleR", mImage, Pos(0.f, 0.f), Size(30.f, 36.f)
			, Vector2(-10.f, 0.f), 1, 0.1f);
		mAnimator->CreateAnimation(L"IdleL", mImage, Pos(0.f, 36.f), Size(30.f, 36.f)
			, Vector2(-10.f, 0.f), 1, 0.1f);

		mAnimator->CreateAnimation(L"WalkR", mImage, Pos(0.0f, 72.0f), Size(18.0f, 33.0f)
			, Vector2(-10.0f, 0.0f), 8, 0.1f);
		mAnimator->CreateAnimation(L"WalkL", mImage, Pos(0.0f, 105.0f), Size(18.0f, 33.0f)
			, Vector2(-10.0f, 0.0f), 8, 0.1f);


		mAnimator->CreateAnimation(L"DubleTabR", mImage, Pos(0.0f, 138.0f), Size(60.0f, 36.0f)
			, Vector2(2.0f, 0.0f), 5, 0.1f);
		mAnimator->CreateAnimation(L"DubleTabL", mImage, Pos(0.0f, 174.0f), Size(60.0f, 36.0f)
			, Vector2(2.0f, 0.0f), 5, 0.1f);

		mAnimator->CreateAnimation(L"FMJR", mImage, Pos(0.0f, 210.0f), Size(96.0f, 33.0f)
			, Vector2(23.0f, 0.0f), 5, 0.1f);
		mAnimator->CreateAnimation(L"FMJL", mImage, Pos(0.0f, 243.0f), Size(96.0f, 33.0f)
			, Vector2(23.0f, 0.0f), 5, 0.1f);

		mAnimator->CreateAnimation(L"DiveR", mImage, Pos(0.0f, 276.0f), Size(36.0f, 36.0f)
			, Vector2(-12.0f, 0.0f), 9, 0.1f);
		mAnimator->CreateAnimation(L"DiveL", mImage, Pos(0.0f, 312.0f), Size(36.0f, 36.0f)
			, Vector2(-12.0f, 0.0f), 9, 0.1f);



	}

	void Player::Tick()
	{
		GameObject::Tick();

		Pos pos = GetPos();
		
		// 애니메이션
		PlayAnim();
		
		// 로직
		if (KEY_PRESSE(eKeyCode::W))
		{
			pos.y -= mSpeed * Time::GetDeltaTime();
		}
		if (KEY_PRESSE(eKeyCode::S))
		{
			pos.y += mSpeed * Time::GetDeltaTime();
		}
		if (KEY_PRESSE(eKeyCode::LEFT))
		{
			pos.x -= mSpeed * Time::GetDeltaTime();
		}		
		if (KEY_PRESSE(eKeyCode::RIGHT))
		{
			pos.x += mSpeed * Time::GetDeltaTime();
		}
		/*if (KEY_DOWN(eKeyCode::Z))
		{
			Projectile* missile = new Projectile;
			Scene* playScene = SceneManager::GetCurScene();
			playScene->AddGameObject(missile, eColliderLayer::Player_Projectile);


			Pos startPos = GetScale() / 2.f;
			Pos missilePos = (pos + startPos) - (missile->GetScale() / 2.f);
			
			missile->SetPos(missilePos);
		}*/

		//mAnimator->mCompleteEvent = std::bind(&Player::ActionComplete, this);
		SetPos(pos);
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
			mAnimator->Play(L"DubleTabR");
		}
		if (KEY_DOWN(eKeyCode::X))
		{
			mAnimator->Play(L"FMJR", false);
		}
		if (KEY_DOWN(eKeyCode::C))
		{
			mAnimator->Play(L"DiveR", false);
		}

		if (KEY_UP(eKeyCode::RIGHT))
		{
			mAnimator->Play(L"IdleR", true);
		}
		if (KEY_UP(eKeyCode::LEFT))
		{
			mAnimator->Play(L"IdleL", true);
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
	void Player::ActionComplete()
	{
		mAnimator->Play(L"IdleR", true);
	}
}