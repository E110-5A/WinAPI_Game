#include "jsProjectile.h"
#include "jsTime.h"
#include "jsCollider.h"
#include "jsCamera.h"

namespace js
{
	Projectile::Projectile()
		: m_fSpeed(800.f)
	{
		SetScale(Size(60.f, 20.f));
		Collider* myCollider = new Collider();

		myCollider->SetScale(Size(60.f, 20.f));
		AddComponent(myCollider);

	}
	Projectile::~Projectile()
	{
	}
	void Projectile::Tick()
	{
		Pos pos = GetPos();
		pos.x += m_fSpeed * Time::GetDeltaTime();
		SetPos(pos);

		GameObject::Tick();
	}
	void Projectile::Render(HDC hdc)
	{
		Pos pos = GetPos();
		Size scale = GetScale();
		pos = Camera::CalculatePos(pos);

		Ellipse(hdc, pos.x, pos.y,
			pos.x + scale.x, pos.y + scale.y);

		GameObject::Render(hdc);
	}
	void Projectile::OnCollisionEnter(Collider* other)
	{
		this->Death();
	}
	void Projectile::OnCollisionStay(Collider* other)
	{
	}
	void Projectile::OnCollisionExit(Collider* other)
	{
	}
}