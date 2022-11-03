#include "jsProjectile.h"
#include "jsTime.h"
#include "jsCollider.h"
#include "jsCamera.h"

namespace js
{
	Projectile::Projectile()
		: mSpeed(5000.f)
		, mLifeTime(0.1f)
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
		GameObject::Tick();
		mLifeTime -= Time::GetDeltaTime();
		if (0.f >= mLifeTime)
		{
			this->Death();
		}

		Pos pos = GetPos();
		pos.x += mSpeed * Time::GetDeltaTime();
		SetPos(pos);

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