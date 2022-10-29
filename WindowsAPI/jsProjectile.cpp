#include "jsProjectile.h"
#include "jsTime.h"
namespace js
{
	Projectile::Projectile()
		: m_fSpeed(800.f)
	{
		SetScale(Size(20.f, 60.f));
	}
	Projectile::~Projectile()
	{
	}
	void Projectile::Tick()
	{
		Pos pos = GetPos();
		pos.y -= m_fSpeed * Time::GetDeltaTime();
		SetPos(pos);
	}
	void Projectile::Render(HDC _hdc)
	{
		Pos pos = GetPos();
		Size scale = GetScale();

		Ellipse(_hdc, pos.x, pos.y,
			pos.x + scale.x, pos.y + scale.y);
	}
}