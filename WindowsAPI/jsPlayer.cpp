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
		// 내 이미지 세팅
		if (nullptr == mImage)
		{
			mImage = Resources::Load<Image>
				(L"Player", L"..\\Resources\\Image\\Player\\player.bmp");
		}

		// 콜라이더 설정
		Collider* myCollider = new Collider;
		myCollider->SetPos(GetPos());
		myCollider->SetScale(Size(5.f, 12.f) * GetScale());
		myCollider->SetOffset(Vector2(-12.f, 0.f));
		AddComponent(myCollider);
			
		// 애니메이터 설정
		mAnimator = new Animator;
		mAnimator->CreateAnimation(L"Idle", mImage, Pos(0.f, 0.f), Size(30.f, 36.f)
			, Vector2(0.f, 0.f), 1, 0.1f);
		mAnimator->CreateAnimation(L"WalkRight", mImage, Pos(0.0f, 36.0f), Size(18.0f, 33.0f)
			, Vector2(0.0f, 0.0f), 8, 0.1f);
		mAnimator->CreateAnimation(L"DubleTab", mImage, Pos(0.0f, 69.0f), Size(60.0f, 36.0f)
			, Vector2(0.0f, 0.0f), 5, 0.1f);

		mAnimator->Play(L"Idle");

		AddComponent(mAnimator);
	}

	void Player::Tick()
	{
		GameObject::Tick();

		Pos pos = GetPos();
		
		if (KEY_DOWN(eKeyCode::A))
		{
			mAnimator->Play(L"WalkRight", true);
		}
		if (KEY_DOWN(eKeyCode::D))
		{
			mAnimator->Play(L"WalkRight", true);
		}
		if (KEY_DOWN(eKeyCode::J))
		{
			mAnimator->Play(L"DubleTab");
		}

		if (KEY_UP(eKeyCode::A))
		{
			mAnimator->Play(L"Idle", true);
		}
		if (KEY_UP(eKeyCode::D))
		{
			mAnimator->Play(L"Idle", true);
		}
		if (KEY_UP(eKeyCode::J))
		{
			mAnimator->Play(L"Idle", true);
		}

		/*
		if (KEY_PRESSE(eKeyCode::W))
		{
			pos.y -= mSpeed * Time::GetDeltaTime();
		}
		if (KEY_PRESSE(eKeyCode::A))
		{
			pos.x -= mSpeed * Time::GetDeltaTime();
		}
		if (KEY_PRESSE(eKeyCode::S))
		{
			pos.y += mSpeed * Time::GetDeltaTime();
		}
		if (KEY_PRESSE(eKeyCode::D))
		{
			pos.x += mSpeed * Time::GetDeltaTime();
		}*/
		/*if (KEY_DOWN(eKeyCode::SPACE))
		{
			Projectile* missile = new Projectile;
			Scene* playScene = SceneManager::GetCurScene();
			playScene->AddGameObject(missile, eColliderLayer::Player_Projectile);


			Pos startPos = GetScale() / 2.f;
			Pos missilePos = (pos + startPos) - (missile->GetScale() / 2.f);
			
			missile->SetPos(missilePos);
		}*/

		mAnimator->mCompleteEvent = std::bind(&Player::WalkComplete, this);

		SetPos(pos);
	}
	void Player::Render(HDC hdc)
	{

		GameObject::Render(hdc);
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
}