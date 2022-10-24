#include "jsProjectile.h"
#include "jsTime.h"
namespace js
{
	jsProjectile::jsProjectile()
		: m_fSpeed(800.f)
	{
		SetScale(Size(20.f, 60.f));
	}
	jsProjectile::~jsProjectile()
	{
	}
	void jsProjectile::Tick()
	{
		Pos pos = GetPos();
		pos.y -= m_fSpeed * jsTime::GetDeltaTime();
		SetPos(pos);
	}
	void jsProjectile::Render(HDC _hdc)
	{
		Pos pos = GetPos();
		Size scale = GetScale();

		Ellipse(_hdc, pos.x, pos.y,
			pos.x + scale.x, pos.y + scale.y);
	}
}