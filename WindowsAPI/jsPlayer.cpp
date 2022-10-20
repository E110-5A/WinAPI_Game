#include "jsPlayer.h"

namespace js
{
	jsPlayer::jsPlayer()
		: m_Speed(0.01f)
	{
		SetPos(Pos(100.f, 100.f));
		SetScale(Size(100.f, 100.f));
	}
	jsPlayer::~jsPlayer()
	{
	}
	void jsPlayer::Tick()
	{
		Pos pos = GetPos();
		if (GetAsyncKeyState('W') & 0x8000)
		{
			pos.y -= m_Speed;
		}
		if (GetAsyncKeyState('A') & 0x8000)
		{
			pos.x -= m_Speed;
		}
		if (GetAsyncKeyState('S') & 0x8000)
		{
			pos.y += m_Speed;
		}
		if (GetAsyncKeyState('D') & 0x8000)
		{
			pos.x += m_Speed;
		}
		SetPos(pos);
	}
	void jsPlayer::Render(HDC _dc)
	{
		Pos pos = GetPos();
		Size scale = GetScale();

		Rectangle(_dc, pos.x, pos.y,
			pos.x + scale.x, pos.y + scale.y);
	}
}