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
			SetSpeed(rand() % 800);
			curPos.x = rand() % 1921;
			curPos.y = 100.f;
		}
		curPos.y += m_Speed * jsTime::GetDeltaTime();
		SetPos(curPos);

		
	}
	void jsRain::Render(HDC _hdc)
	{
		Pos pos = GetPos();
		Size scale = GetScale();

		Ellipse(_hdc, pos.x, pos.y,
			pos.x + scale.x, pos.y + scale.y);
	}
}