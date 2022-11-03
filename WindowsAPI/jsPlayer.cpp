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
				(L"Player", L"..\\Resources\\Image\\Player\\idle.bmp");
		}

		// 콜라이더 설정
		Collider* myCollider = new Collider;
		myCollider->SetPos(GetPos());
		myCollider->SetScale(Size(5.f, 12.f) * GetScale());
		myCollider->SetOffset(Vector2(-12.f, 0.f));
		AddComponent(myCollider);

		// 애니메이터 설정
		AddComponent(new Animator);
	}

	void Player::Tick()
	{
		GameObject::Tick();

		Pos pos = GetPos();
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
		}
		if (KEY_DOWN(eKeyCode::SPACE))
		{
			Projectile* missile = new Projectile;
			Scene* playScene = SceneManager::GetCurScene();
			playScene->AddGameObject(missile, eColliderLayer::Player_Projectile);


			Pos startPos = GetScale() / 2.f;
			Pos missilePos = (pos + startPos) - (missile->GetScale() / 2.f);
			
			missile->SetPos(missilePos);
		}
		SetPos(pos);
	}
	void Player::Render(HDC hdc)
	{
		Pos pos = GetPos();
		Size scale = GetScale();

		Vector2 finalPos;
		finalPos.x = (pos.x - mImage->GetWidth() * (scale.x / 2.f));
		finalPos.y = (pos.y - mImage->GetHeight() * (scale.y / 2.f));

		finalPos = Camera::CalculatePos(finalPos);

		Vector2 rect;
		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;

		BLENDFUNCTION func = {};
		func.AlphaFormat = AC_SRC_ALPHA;
		func.BlendOp = AC_SRC_OVER;
		func.BlendFlags = 0;
		func.SourceConstantAlpha = 255;

		AlphaBlend(hdc,
			finalPos.x, finalPos.y,
			rect.x, rect.y,
			mImage->GetDC(), 0, 0,
			mImage->GetWidth(), mImage->GetHeight(), func);

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
}