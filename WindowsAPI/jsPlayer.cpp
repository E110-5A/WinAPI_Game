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

namespace js
{
	Player::Player()
		: mSpeed(400.f)
		, mImage(nullptr)
	{
		// 내 초기값 세팅
		SetPos(Pos(100.f, 100.f));
		SetScale(Size(3.f, 3.f));

		// 내 이미지 세팅
		if (nullptr == mImage)
		{
			mImage = Resources::Load<Image>
				(L"Player", L"..\\Resources\\Image\\Player\\idle.bmp");
		}
		// 컴포넌트 부착
		AddComponent(new Animator);
		AddComponent(new Collider);

		// 컴포넌트 초기화
		Collider* myCollider = GetComponent<Collider>();
		myCollider->SetPos(GetPos());
	}
	Player::~Player()
	{
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

		Vector2 rect;
		rect.x = mImage->GetWidth() * scale.x;
		rect.y = mImage->GetHeight() * scale.y;


		TransparentBlt(hdc, 
			finalPos.x, finalPos.y,
			rect.x, rect.y,
			mImage->GetDC(), 0, 0, 
			mImage->GetWidth(), mImage->GetHeight(), RGB(255,0,255));

		GameObject::Render(hdc);
	}
}