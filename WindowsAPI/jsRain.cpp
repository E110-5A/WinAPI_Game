#include "jsRain.h"
#include "jsTime.h"
namespace js
{
	jsRain::jsRain()
		: m_Speed(400.f)
	{
	}
	jsRain::~jsRain()
	{
	}

	void jsRain::Tick()
	{
		Pos curPos = GetPos();

		if (curPos.y >= 1000.f)
		{
			SetSpeed(300 + rand() % 400);
			curPos.x = rand() % 1921;
			curPos.y = rand() % 100;
			SetRGB(rand() % 255, rand() % 255, rand() % 255);
		}
		curPos.y += m_Speed * Time::GetDeltaTime();
		SetPos(curPos);
		
		
	}
	void jsRain::Render(HDC _hdc)
	{
		HBRUSH randBrush = CreateSolidBrush(RGB(R,G,B));
		Brush brush(_hdc, randBrush);

		HPEN randPen = CreatePen(PS_SOLID, 1, RGB(R, G, B));
		Pen pen(_hdc, randPen);
		Pos pos = GetPos();
		Size scale = GetScale();

		Ellipse(_hdc, pos.x, pos.y,
			pos.x + scale.x, pos.y + scale.y);
	}
}