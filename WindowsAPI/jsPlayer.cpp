#include "jsPlayer.h"
#include "jsTime.h"
#include "jsInput.h"
#include "jsProjectile.h"
#include "jsSceneManager.h"
#include "jsScene.h"

namespace js
{
	jsPlayer::jsPlayer()
		: m_Speed(400.f)
	{
		SetPos(Pos(100.f, 700.f));
		SetScale(Size(70.f, 70.f));
	}
	jsPlayer::~jsPlayer()
	{
	}

	void jsPlayer::Tick()
	{
		Pos pos = GetPos();
		if (KEY_PRESSE(eKeyCode::W))
		{
			pos.y -= m_Speed * jsTime::GetDeltaTime();
		}
		if (KEY_PRESSE(eKeyCode::A))
		{
			pos.x -= m_Speed * jsTime::GetDeltaTime();
		}
		if (KEY_PRESSE(eKeyCode::S))
		{
			pos.y += m_Speed * jsTime::GetDeltaTime();
		}
		if (KEY_PRESSE(eKeyCode::D))
		{
			pos.x += m_Speed * jsTime::GetDeltaTime();
		}
		if (KEY_DOWN(eKeyCode::SPACE))
		{
			jsProjectile* missile = new jsProjectile;
			jsScene* playScene = jsSceneManager::GetCurScene();
			playScene->AddGameObject(missile);


			Pos startPos = GetScale() / 2.f;
			Pos missilePos = (pos + startPos) - (missile->GetScale() / 2.f);
			
			missile->SetPos(missilePos);
		}
		SetPos(pos);
	}
	void jsPlayer::Render(HDC _hdc)
	{
		HBRUSH blueBrush = CreateSolidBrush(RGB(153, 204, 255));
		Brush brush(_hdc, blueBrush);

		HPEN greenPen = CreatePen(PS_SOLID, 1, RGB(153, 255, 204));
		Pen pen(_hdc, greenPen);

		Pos pos = GetPos();
		Size scale = GetScale();

		Rectangle(_hdc, pos.x, pos.y,
			pos.x + scale.x, pos.y + scale.y);

	}
}