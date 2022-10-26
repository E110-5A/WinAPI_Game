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
		SetPos(Pos(100.f, 100.f));
		SetScale(Size(3.f, 3.f));

		if (nullptr == mImage)
		{
			mImage = Resources::Load<Image>(L"Player", L"..\\Resources\\Image\\Player\\idlex3.bmp");
		}
		AddComponent(new Animator);
		AddComponent(new Collider);
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
			pos.y -= mSpeed * jsTime::GetDeltaTime();
		}
		if (KEY_PRESSE(eKeyCode::A))
		{
			pos.x -= mSpeed * jsTime::GetDeltaTime();
		}
		if (KEY_PRESSE(eKeyCode::S))
		{
			pos.y += mSpeed * jsTime::GetDeltaTime();
		}
		if (KEY_PRESSE(eKeyCode::D))
		{
			pos.x += mSpeed * jsTime::GetDeltaTime();
		}
		if (KEY_DOWN(eKeyCode::SPACE))
		{
			Projectile* missile = new Projectile;
			Scene* playScene = SceneManager::GetCurScene();
			playScene->AddGameObject(missile);


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

		//HBRUSH blueBrush = CreateSolidBrush(RGB(153, 204, 255));
		//Brush brush(hdc, blueBrush);

		//HPEN greenPen = CreatePen(PS_SOLID, 1, RGB(153, 255, 204));
		//Pen pen(hdc, greenPen);

		//Rectangle(hdc, pos.x, pos.y,
		//	pos.x + scale.x, pos.y + scale.y);


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