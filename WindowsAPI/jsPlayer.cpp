#include "jsPlayer.h"
#include "jsTime.h"
#include "jsInput.h"
#include "jsProjectile.h"
#include "jsSceneManager.h"
#include "jsScene.h"
#include "jsImage.h"
#include "jsResources.h"

namespace js
{
	jsPlayer::jsPlayer()
		: m_Speed(400.f)
		, m_Image(nullptr)
	{
		SetPos(Pos(100.f, 500.f));
		SetScale(Size(20.f, 60.f));

		if (nullptr == m_Image)
		{
			m_Image = jsResources<jsImage>::Load(L"Player", L"..\\Resources\\Image\\Player\\idlex3.bmp");
			
		}
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
	void jsPlayer::Render(HDC hdc)
	{
		Pos pos = GetPos();
		Size scale = GetScale();

		//HBRUSH blueBrush = CreateSolidBrush(RGB(153, 204, 255));
		//Brush brush(hdc, blueBrush);

		//HPEN greenPen = CreatePen(PS_SOLID, 1, RGB(153, 255, 204));
		//Pen pen(hdc, greenPen);

		//Rectangle(hdc, pos.x, pos.y,
		//	pos.x + scale.x, pos.y + scale.y);

		
		BitBlt(hdc, pos.x, pos.y,
			m_Image->GetWidth(), m_Image->GetHeight(),
			m_Image->GetDC(), 0, 0, SRCCOPY);
	}
}